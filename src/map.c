#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "map.h"

#define BRIDGE_MAP_CAPACITY 16

typedef struct BridgeKeyVal {
    BridgePair *pair;
    struct BridgeKeyVal *next;
} BridgeKeyVal;

struct BridgeMap {
    int size;
    int k_type;
    int v_type;
    int kv_size;
    int capacity;
    void *count;
    void *tables;
} BridgeMap;

unsigned int utf8_hash(const char *str) {
    unsigned int hash = 5381;
    while (*str) {
        // 计算UTF-8编码的字符长度
        unsigned int len = 0;
        unsigned char c = (unsigned char)*str;
        if ((c & 0x80) == 0) {
            len = 1;
        } else if ((c & 0xE0) == 0xC0) {
            len = 2;
        } else if ((c & 0xF0) == 0xE0) {
            len = 3;
        } else if ((c & 0xF8) == 0xF0) {
            len = 4;
        }
        // 对每个字符进行哈希运算
        for (unsigned int i = 0; i < len; i++) {
            hash = ((hash << 5) + hash) + (unsigned int)*str;
            str++;
        }
    }

    return hash;
}

BridgeMap *bmap_create(BridgeNodeType k_type, BridgeNodeType v_type)
{
    assert(k_type > B_Invalid && k_type < B_Maximum);
    assert(v_type > B_Invalid && v_type < B_Maximum);

    BridgeMap *map = malloc(sizeof(BridgeMap));

    assert(map);

    map->size = 0;
    map->k_type = k_type;
    map->v_type = v_type;
    map->kv_size = sizeof(BridgeKeyVal);
    map->capacity = BRIDGE_MAP_CAPACITY;
    map->k_size = malloc(map->capacity * sizeof(int));
    map->tables = malloc(map->capacity * map->kv_size);

    assert(map->k_size);
    memset(map->k_size, 0, map->capacity * sizeof(int));

    assert(map->tables);
    memset(map->tables, 0, map->capacity * map->kv_size);

    return map;
}

void bvector_destroy(BridgeMap *map)
{
    BridgeKeyVal *kv = NULL;
    BridgeKeyVal *next = NULL;
    for (int i = 0; i < map->capacity; i++) {
        kv = (BridgeKeyVal *)(map->tables + (i * map->kv_size));
        if (!kv) {
            continue;
        }

        kv = kv->next;
        while (kv) {
            next = kv->next;
            free(kv->key);
            free(kv->val);
            free(kv);
            kv = next;
        }
    }

    free(map->tables);
    free(map);
}

void bmap_put_pair(BridgeMap *map, BridgePair *pair)
{
    assert(map && pair && pair->first && pair->second);
    assert(map->k_type == pair->first->type);
    assert(map->v_type == pair->second->type);

    int index;
    int *count = NULL;
    BridgeKeyVal *kv = NULL;
    BridgeKeyVal *new_kv = NULL;

    index = bmap_hash_node(pair->first) % map->capacity;

    count = (int *)(map->k_size + (index * sizeof(int)));
    if (*count == 0) {
        memcpy(map->tables + (index * map->size), bmap_kv_create(pair), map->kv_size);
        goto success;
    }

    kv = *(BridgeKeyVal *)(map->tables + (index * map->kv_size));
    assert(kv && kv->pair);

    while (kv) {
        if (bnode_is_equal(bpair_first_node(kv->pair), bpair_first_node(pair))) {
            bnode_value_move(bpair_second_node(kv->pair), bpair_second_node(pair));
            goto success;
        }

        if (!kv->next) {
            kv->next = bmap_kv_create(pair);
            goto success;
        }

        kv = kv->next;
        continue;
    }

success:
    (*count)++;
    map->size++;

    bmap_table_rehash(map);
}

void* hash_map_get(HashMap* map, const void* key) {
    size_t index = map->hash_func(key, map->key_size) % map->capacity;
    Entry* entry = map->table[index];
    while (entry) {
        if (map->key_eq_func(entry->key, key, map->key_size)) {
            return entry->value;
        }
        entry = entry->next;
    }
    return NULL;
}

void hash_map_remove(HashMap* map, const void* key) {
    size_t index = map->hash_func(key, map->key_size) % map->capacity;
    Entry* entry = map->table[index];
    Entry* prev = NULL;
    while (entry) {
        if (map->key_eq_func(entry->key, key, map->key_size)) {
            if (prev) {
                prev->next = entry->next;
            } else {
                map->table[index] = entry->next;
            }
            free(entry->key);
            free(entry->value);
            free(entry);
            map->size--;
            return;
        }
        prev = entry;
        entry = entry->next;
    }
}
