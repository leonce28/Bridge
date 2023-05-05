#pragma once

#include "node.h"

typedef struct BridgePair BridgePair;
extern BridgePair *bpair_make(BridgeNode *first, BridgeNode *second);

extern inline BridgeNode *bpair_first_node(BridgePair *pair);
extern inline BridgeNode *bpair_second_node(BridgePair *pair);