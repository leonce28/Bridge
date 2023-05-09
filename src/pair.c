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
