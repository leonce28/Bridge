#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "map.h"

#define BRIDGE_MAP_CAPACITY 16

typedef struct MapListNode {
    BridgePair *pair;
    struct MapListNode *next;
} MapListNode;

typedef struct MapListRoot {
    int count;
    MapListNode *root;
} MapListRoot;

struct BridgeMap {
    int size;
    int capacity;
    int key_type;
    int val_type;
    int block_size;
    void *tables;
};

MapListNode *bmap_node_create(BridgePair *pair)
{
    assert(pair);

    MapListNode *node = malloc(sizeof(MapListNode));

    node->pair = pair;
    node->next = NULL;

    return node;
}

unsigned int bmap_hash_integer(long long integer)
{
    return integer;
}

unsigned int bmap_hash_decimal(long double decimal)
{
    return (unsigned int)(decimal * 31);
}

unsigned int bmap_hash_string(const char *string)
{
    unsigned char c;
    unsigned int i, len;
    unsigned int hash = 5381;

    while (*string) {

        c = (unsigned char)*string;
        if ((c & 0x80) == 0) {
            len = 1;
        } else if ((c & 0xE0) == 0xC0) {
            len = 2;
        } else if ((c & 0xF0) == 0xE0) {
            len = 3;
        } else if ((c & 0xF8) == 0xF0) {
            len = 4;
        } else {
            len = 0;
        }

        for (i = 0; i < len; i++) {
            hash = ((hash << 5) + hash) + (unsigned int)*string;
            string++;
        }
    }

    return hash;
}

unsigned int bmap_hash_object(const void *object, int length)
{
    // undo
    return length;
}

unsigned int bmap_hash_node(const BridgeNode *node)
{
    assert(node);

    unsigned int value = 0;
    switch (bnode_type(node)) {
        case B_Integer:
            value = bmap_hash_integer(bnode_to_integer(node));
            break;
        case B_Decimal:
            value = bmap_hash_decimal(bnode_to_decimal(node));
            break;
        case B_String:
            value = bmap_hash_string(bnode_to_string(node));
            break;
        case B_Object:
            value = bmap_hash_object(bnode_to_object(node), bnode_length(node));
            break;
        case B_Invalid:
        case B_Maximum:
        default:
            break;
    }

    return value;
}

void bmap_rehash(BridgeMap *map)
{
    assert(map);

    assert(map->size < map->capacity);
}


BridgeMap *bmap_create(BridgeNodeType key_type, BridgeNodeType val_type)
{
    assert(key_type > B_Invalid && key_type < B_Maximum);
    assert(val_type > B_Invalid && val_type < B_Maximum);

    BridgeMap *map = malloc(sizeof(BridgeMap));

    assert(map);

    map->size = 0;
    map->key_type = key_type;
    map->val_type = val_type;
    map->block_size = sizeof(MapListNode);
    map->capacity = BRIDGE_MAP_CAPACITY;
    map->tables = malloc(map->capacity * map->block_size);

    assert(map->tables);
    memset(map->tables, 0, map->capacity * map->block_size);

    return map;
}

void bmap_destroy(BridgeMap *map)
{
    MapListNode *kv = NULL;
    MapListNode *next = NULL;
    for (int i = 0; i < map->capacity; i++) {
        kv = (MapListNode *)(map->tables + (i * map->block_size));
        if (!kv) {
            continue;
        }

        kv = kv->next;
        while (kv) {
            next = kv->next;
            bpair_destroy(kv->pair);
            free(kv);
            kv = next;
        }
    }

    free(map->tables);
    free(map);
}

void bmap_put_pair(BridgeMap *map, BridgePair *pair)
{
    assert(map && pair);

    int index;
    int *count = NULL;
    MapListRoot *root = NULL;
    MapListNode *node = NULL;
    MapListNode *new_kv = NULL;
    const BridgeNode *first = bpair_first(pair);
    const BridgeNode *second = bpair_second(pair);

    if (map->key_type != bnode_type(first) || map->val_type != bnode_type(second)) {
        return;
    }

    index = bmap_hash_node(first) % map->capacity;
    root = (MapListRoot *)(map->tables + (index * map->block_size));
    assert(root);

    if (root->count == 0) {
        root->root = bmap_node_create(pair);
        goto success;
    }

    node = root->root;
    while (node) {
        if (bnode_is_equal(bpair_first(node->pair), bpair_first(pair))) {
            bnode_transfer(bpair_second(node->pair), bpair_second(pair));
            goto success;
        }

        if (!node->next) {
            node->next = bmap_node_create(pair);
            goto success;
        }

        node = node->next;
        continue;
    }

success:
    root->count++;
    bmap_rehash(map);
}

BridgePair *bmap_find_pair(const BridgeMap *map, const BridgeNode *first) 
{
    assert(map && first);

    int index, *count;
    MapListRoot *root = NULL;
    MapListNode *node = NULL;

    index = bmap_hash_node(first) % map->capacity;
    root = (MapListRoot *)(map->tables + (index * map->block_size));
    assert(root);

    if (root->count == 0) {
        return nullptr;
    }

    for (node = root->root; 
         node && bnode_not_equal(bpair_first(node->pair), first); 
         node = node->next) { }

    if (node && node->pair) {
        return node->pair;
    }

    return nullptr;
}

void bmap_erase_pair(BridgeMap *map, const BridgeNode *first)
{
    assert(map && first);

    int index;
    MapListRoot *root = NULL;
    MapListNode *node = NULL, *prev = NULL;

    index = bmap_hash_node(first) % map->capacity;
    root = (MapListRoot *)(map->tables + (index * map->block_size));
    assert(root);

    if (root->count == 0) {
        return;
    }

    node = root->root;
    assert(node && node->pair);

    while (node && bnode_not_equal(bpair_first(node->pair), first)) {
        prev = node;
        node = node->next;
    }

    if (prev) {
        prev->next = node->next;
        root->count--;
    } else {
        root->count = 0;
        root->root = NULL;
    }

    bpair_destroy(node->pair);
    free(node);
}

void bmap_print_normal(const BridgeMap *map)
{

}

void bmap_print_callback(const BridgeMap *map, BridgeMapPrint print)
{
    assert(map && print);
    
    int index = 0;
    MapListRoot *root = NULL;
    MapListNode *node = NULL;
    for (; index < map->capacity; ++index) {
        root = (MapListRoot *)(map->tables + (index * map->block_size));
        if (root && root->count == 0) {
            continue;
        }

        node = root->root;
        while (node) {
            print(bnode_to_object(bpair_first(node->pair)), 
                  bnode_to_object(bpair_second(node->pair)));
            node = node->next;
        }
    }
}