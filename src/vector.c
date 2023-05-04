#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "vector.h"
#include "node.h"

#define BRIDGE_VECTOR_CAPACITY      16
#define BRIDGE_VECTOR_EXPAND_RATIO  2

struct BridgeVector {
    int type;
    int size;
    int esize;
    int capacity;
    void *elements;
};

BridgeVector *bvector_create()
{
    BridgeVector *vector = malloc(sizeof(BridgeVector));

    assert(vector);

    vector->size = 0;
    vector->capacity = BRIDGE_VECTOR_CAPACITY;
    vector->esize = sizeof(BridgeNode);
    vector->elements = malloc(vector->capacity * vector->esize);

    assert(vector->elements);

    return vector;
}

void bvector_destroy(BridgeVector *vector) 
{
    free(vector->elements);
    free(vector);
}

void bvector_expand(BridgeVector *vector)
{
    assert(vector);

    vector->capacity *= BRIDGE_VECTOR_EXPAND_RATIO;
    vector->elements = realloc(vector->elements, vector->capacity * vector->esize);

    assert(vector->elements);
}

void bvector_append(BridgeVector *vector, BridgeNode *node)
{
    assert(vector && node);

    if (vector->type == B_Invalid) {
        vector->type = node->type;
    }

    assert(vector->type == node->type);

    if (vector->size == vector->capacity) { 
        bvector_expand(vector);
    }

    memcpy(vector->elements + vector->size * vector->esize, node, vector->esize);

    vector->size++;
}

void bvector_append_ival(BridgeVector *vector, long long ival)
{
    bvector_append(vector, bnode_create_ival(ival));
}

void bvector_append_dval(BridgeVector *vector, long double dval)
{
    bvector_append(vector, bnode_create_dval(dval));
}

void bvector_append_sval(BridgeVector *vector, const char *sval)
{
    bvector_append(vector, bnode_create_sval(sval));
}

void bvector_append_pval(BridgeVector *vector, void *pval)
{
    bvector_append(vector, bnode_create_pval(pval));
}

BridgeNode *bvector_fetch(BridgeVector *vector, int index) 
{
    assert(vector && index < vector->size);

    return vector->elements + index * vector->esize;
}

long long bvector_fetch_ival(BridgeVector *vector, int index)
{
    assert(vector && vector->type == B_Integer);

    BridgeNode *node = bvector_fetch(vector, index);

    assert(node);

    return node->val.ival;
}

long double bvector_fetch_dval(BridgeVector *vector, int index)
{
    assert(vector && vector->type == B_Decimal);

    BridgeNode *node = bvector_fetch(vector, index);

    assert(node);

    return node->val.dval;
}

const char *bvector_fetch_sval(BridgeVector *vector, int index)
{
    assert(vector && vector->type == B_String);

    BridgeNode *node = bvector_fetch(vector, index);

    assert(node);

    return node->val.sval;
}

void *bvector_fetch_pval(BridgeVector *vector, int index)
{
    assert(vector && vector->type == B_Pointer);

    BridgeNode *node = bvector_fetch(vector, index);

    assert(node);

    return node->val.pval;
}

void bvector_modify_ival(BridgeVector *vector, int index, long long ival)
{
    assert(vector && vector->type == B_Integer);

    BridgeNode *node = bvector_fetch(vector, index);

    assert(node);

    node->val.ival = ival;
}

void bvector_modify_dval(BridgeVector *vector, int index, long double dval)
{
    assert(vector && vector->type == B_Decimal);

    BridgeNode *node = bvector_fetch(vector, index);

    assert(node);

    node->val.dval = dval;
}

void bvector_modify_sval(BridgeVector *vector, int index, const char *sval)
{
    int l1, l2;
    assert(vector && vector->type == B_String && sval);

    BridgeNode *node = bvector_fetch(vector, index);

    assert(node);

    l1 = strlen(node->val.sval);
    l2 = strlen(sval);

    if (l2 > l1) {
        node->val.sval = realloc(node->val.sval, l2 + 1);
    }

    strncpy(node->val.sval, sval, l2);

    node->val.sval[l2] = '\0';
}

void bvector_modify_pval(BridgeVector *vector, int index, void *pval)
{
    void *old = NULL;
    assert(vector && vector->type == B_Pointer && pval);

    BridgeNode *node = bvector_fetch(vector, index);

    assert(node);

    old = node->val.pval;
    node->val.pval = pval;

    free(old);
}

void bvector_print_normal(const BridgeVector *vector)
{
    assert(vector);

    BridgeNode *node = NULL;

    for (int i = 0; i < vector->size; ++i) {
        node = (BridgeNode *)(vector->elements + i * vector->esize);

        switch (node->type) {
            case B_Integer:
                printf("%lld ", node->val.ival);
                break;
            case B_Decimal:
                printf("%Lf ", node->val.dval);
                break;
            case B_String:
                printf("%s ", node->val.sval);
                break;
            case B_Pointer:
                printf("%p ", node->val.pval);
                break;
        }
    }
}

void bvector_print_callback(const BridgeVector *vector, BridgeVectorPrint print)
{
    assert(vector && print);

    BridgeNode *node = NULL;

    for (int i = 0; i < vector->size; ++i) {
        node = (BridgeNode *)(vector->elements + i * vector->esize);
        print(node->val.pval);
    }
}

int bvector_size(BridgeVector *vector) 
{
    return vector->size;
}


