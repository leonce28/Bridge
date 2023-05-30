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
    int tb_size;
    int capacity;
    void *tables;

    BridgeFuncFree free;
    BridgeFuncHash hash;
    BridgeFuncTostr tostr;
    BridgeFuncCompare compare;
};

struct BridgePair {
    BridgeNode *first;
    BridgeNode *second;
};

BridgePair *bpair_make(BridgeNode *first, BridgeNode *second)
{
    assert(first && second);

    BridgePair *pair = malloc(sizeof(BridgePair));

    assert(pair);

    pair->first = first;
    pair->second = second;

    return pair;
}

void bpair_destroy(BridgePair *pair)
{
    assert(pair);

    free(pair->first);
    free(pair->second);
}

BridgeNode *bpair_first(BridgePair *pair)
{
    return pair->first;
}

BridgeNode *bpair_second(BridgePair *pair)
{
    return pair->second;
}

MapListNode *bmap_node_create(BridgePair *pair)
{
    assert(pair);

    MapListNode *node = malloc(sizeof(MapListNode));

    node->pair = pair;
    node->next = NULL;

    return node;
}

void bmap_rehash(BridgeMap *map)
{
    assert(map);

    assert(map->size < map->capacity);
}


BridgeMap *bmap_create()
{
    BridgeMap *map = malloc(sizeof(BridgeMap));

    assert(map);

    map->size = 0;
    map->tb_size = sizeof(MapListNode);
    map->capacity = BRIDGE_MAP_CAPACITY;
    map->tables = malloc(map->capacity * map->tb_size);

    assert(map->tables);

    memset(map->tables, 0, map->capacity * map->tb_size);

    return map;
}

void bmap_destroy(BridgeMap *map)
{
    MapListNode *kv = NULL;
    MapListNode *next = NULL;
    for (int i = 0; i < map->capacity; i++) {
        kv = (MapListNode *)(map->tables + (i * map->tb_size));
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

unsigned int bmap_hash_node(const BridgeNode *node, const BridgeMap *map)
{
    assert(node && map);

    unsigned int index = 0;
    
    if (map->hash) {
        index = map->hash(bnode_to_void(node));
    } else {
        index = bnode_hash(node);
    }

    return index % map->capacity;
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

    index = bmap_hash_node(first, map);
    root = (MapListRoot *)(map->tables + (index * map->tb_size));
    assert(root);

    if (root->count == 0) {
        root->root = bmap_node_create(pair);
        goto success;
    }

    node = root->root;
    while (node) {
        if (bnode_equal(bpair_first(node->pair), bpair_first(pair))) {
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
    // bmap_rehash(map);
}

BridgePair *bmap_find_pair(const BridgeMap *map, const BridgeNode *first) 
{
    assert(map && first);

    int index, *count;
    MapListRoot *root = NULL;
    MapListNode *node = NULL;

    index = bmap_hash_node(first, map);
    root = (MapListRoot *)(map->tables + (index * map->tb_size));
    assert(root);

    if (root->count == 0) {
        return nullptr;
    }

    for (node = root->root; 
         node && !bnode_equal(bpair_first(node->pair), first); 
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

    index = bmap_hash_node(first, map);
    root = (MapListRoot *)(map->tables + (index * map->tb_size));
    assert(root);

    if (root->count == 0) {
        return;
    }

    node = root->root;
    assert(node && node->pair);

    while (node && !bnode_equal(bpair_first(node->pair), first)) {
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

void bmap_udf_free(BridgeMap *map, BridgeFuncFree free)
{
    assert(map && free);

    map->free = free;
}

void bmap_udf_hash(BridgeMap *map, BridgeFuncHash hash)
{
    assert(map && hash);

    map->hash = hash;
}

void bmap_udf_tostr(BridgeMap *map, BridgeFuncTostr tostr)
{
    assert(map && tostr);

    map->tostr = tostr;
}

void bmap_udf_compare(BridgeMap *map, BridgeFuncCompare compare)
{
    assert(map && compare);

    map->compare = compare;
}

void bmap_print(const BridgeMap *map)
{
    bmap_print_len(map, 512);
}

void bmap_print_len(const BridgeMap *map, int len)
{
    assert(map);
    
    int index = 0;
    MapListRoot *root = NULL;
    MapListNode *node = NULL;

    char *dst = (char *)malloc(len + 1);
    dst[0] = '\0';

    for (; index < map->capacity; ++index) {
        root = (MapListRoot *)(map->tables + (index * map->tb_size));
        if (root && root->count == 0) {
            continue;
        }

        node = root->root;
        while (node) {
            if (map->tostr) {
                map->tostr(bnode_to_void(node->pair->first), dst, len);
                printf("%s ", dst);
                map->tostr(bnode_to_void(node->pair->second), dst, len);
                printf("%s ", dst);
            } else {
                bnode_tostr(node->pair->first, dst, len);
                printf("%s ", dst);
                bnode_tostr(node->pair->second, dst, len);
                printf("%s ", dst);
            }

            node = node->next;
        }
    }
}