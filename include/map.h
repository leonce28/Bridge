#pragma once

#include "node.h"
#include "pair.h"


typedef struct BridgeMap BridgeMap;
typedef void(*BridgeMapPrint)(const void *, const void *);

BridgeMap *bmap_create(BridgeNodeType k_type, BridgeNodeType v_type);
void bvector_destroy(BridgeMap *map);

extern void bmap_put_pair(BridgeMap *map, BridgePair *pair);
extern BridgePair *bmap_find_pair(const BridgeMap *map, const BridgeNode *first);
extern void bmap_erase_pair(BridgeMap *map, const BridgeNode *first);

extern void bmap_print_normal(const BridgeMap *map);
extern void bmap_print_callback(const BridgeMap *map, BridgeMapPrint print);


