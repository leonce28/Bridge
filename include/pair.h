#pragma once

#include "node.h"

typedef struct BridgePair BridgePair;
extern BridgePair *bpair_make(BridgeNode *first, BridgeNode *second);
extern void bpair_destroy(BridgePair *pair);

extern BridgeNode *bpair_first(BridgePair *pair);
extern BridgeNode *bpair_second(BridgePair *pair);
