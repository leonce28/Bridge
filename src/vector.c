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

BridgeVector *bvector_create(BridgeNodeType type)
{
    BridgeVector *vector = malloc(sizeof(BridgeVector));

    assert(vector);

    vector->size = 0;
    vector->type = type;
    vector->capacity = BRIDGE_VECTOR_CAPACITY;
    vector->esize = bnode_size();
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

void bvector_append(BridgeVector *vector, const BridgeNode *node)
{
    assert(vector && node && vector->type == bnode_type(node));

    if (vector->size == vector->capacity) { 
        bvector_expand(vector);
    }

    memcpy(vector->elements + vector->size * vector->esize, node, vector->esize);

    vector->size++;
}

BridgeNode *bvector_fetch(BridgeVector *vector, int index) 
{
    assert(vector && index < vector->size);

    return vector->elements + index * vector->esize;
}

void bvector_set_integer(BridgeVector *vector, int index, long long ival)
{
    assert(vector && vector->type == B_Integer);

    BridgeNode *node = bvector_fetch(vector, index);

    assert(node);

    bnode_set_integer(node, ival);
}

void bvector_set_decimal(BridgeVector *vector, int index, long double dval)
{
    assert(vector && vector->type == B_Decimal);

    BridgeNode *node = bvector_fetch(vector, index);

    assert(node);

    bnode_set_decimal(node, dval);
}

void bvector_set_string(BridgeVector *vector, int index, const char *sval)
{
    int l1, l2;
    assert(vector && vector->type == B_String && sval);

    BridgeNode *node = bvector_fetch(vector, index);

    assert(node);

    bnode_set_string(node, sval);
}

void bvector_set_object(BridgeVector *vector, int index, const void *oval, int length)
{
    void *old = NULL;
    assert(vector && vector->type == B_Object && oval);

    BridgeNode *node = bvector_fetch(vector, index);

    assert(node);

    bnode_set_object(node, oval, length);
}

void bvector_print_normal(const BridgeVector *vector)
{
    assert(vector);

    BridgeNode *node = NULL;

    for (int i = 0; i < vector->size; ++i) {
        node = (BridgeNode *)(vector->elements + i * vector->esize);

        switch (bnode_type(node)) {
            case B_Integer:
                printf("%lld ", bnode_to_integer(node));
                break;
            case B_Decimal:
                printf("%Lf ", bnode_to_decimal(node));
                break;
            case B_String:
                printf("%s ", bnode_to_string(node));
                break;
            case B_Object:
                printf("%p ", bnode_to_object(node));
                break;
            case B_Invalid:
            case B_Maximum:
            default:
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
        print(bnode_object(node));
    }
}

int bvector_size(BridgeVector *vector) 
{
    return vector->size;
}


