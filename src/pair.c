#include <stdlib.h>
#include <assert.h>
#include "pair.h"
#include "node.h"

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


inline BridgeNode *bpair_first_node(BridgePair *pair)
{
    return pair->first;
}

inline BridgeNode *bpair_second_node(BridgePair *pair)
{
    return pair->second;
}
