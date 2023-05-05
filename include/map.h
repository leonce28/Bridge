#pragma once

#include "node.h"
#include "pair.h"

BridgeMap *bmap_create(BridgeNodeType k_type, BridgeNodeType v_type);
void bvector_destroy(BridgeMap *map);

extern void bmap_put_pair(BridgeMap *map, BridgePair *pair);
