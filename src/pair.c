#include <stdlib.h>
#include <assert.h>
#include "pair.h"
#include "node.h"

struct BridgePair {
    void *first;
    void *second;
};

BridgePair *bpair_make(void *first, void *second)
{
    assert(first && second);

    BridgePair *pair = malloc(sizeof(BridgePair));

    assert(pair);

    pair->first = first;
    pair->second = second;

    return pair;
}
