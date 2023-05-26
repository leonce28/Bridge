#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "vector.h"
#include "node.h"

#define BRIDGE_VECTOR_CAPACITY      16
#define BRIDGE_VECTOR_EXPAND_RATIO  2

struct BridgeVector {
    int size;
    int esize;
    int capacity;
    void *elements;
    BridgeFuncFree free;
    BridgeFuncTostr tostr;
    BridgeFuncCompare compare;
};

BridgeVector *bvector_create()
{
    BridgeVector *vector = malloc(sizeof(BridgeVector));

    assert(vector);

    vector->size = 0;
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
    assert(vector && node);

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
    assert(vector);

    BridgeNode *node = bvector_fetch(vector, index);

    assert(node && bnode_type(node) == B_Integer);

    bnode_set_integer(node, ival);
}

void bvector_set_decimal(BridgeVector *vector, int index, long double dval)
{
    assert(vector);

    BridgeNode *node = bvector_fetch(vector, index);

    assert(node && bnode_type(node) == B_Decimal);

    bnode_set_decimal(node, dval);
}

void bvector_set_string(BridgeVector *vector, int index, const char *sval)
{
    int l1, l2;
    assert(vector && sval);

    BridgeNode *node = bvector_fetch(vector, index);

    assert(node && bnode_type(node) == B_String);

    bnode_set_string(node, sval);
}

void bvector_set_object(BridgeVector *vector, int index, void *oval)
{
    void *old = NULL;
    assert(vector && oval);

    BridgeNode *node = bvector_fetch(vector, index);
    assert(node && bnode_type(node) == B_Object);

    void *del = bnode_set_object(node, oval);
    assert(del);

    if (vector->free) {
        vector->free(del);
    } else {
        free(del);
    }
}

void bvector_udf_free(BridgeVector *vector, BridgeFuncFree free)
{
    assert(vector && free);

    vector->free = free;
}

void bvector_udf_tostr(BridgeVector *vector, BridgeFuncTostr tostr)
{
    assert(vector && tostr);

    vector->tostr = tostr;
}

void bvector_udf_compare(BridgeVector *vector, BridgeFuncCompare compare)
{
    assert(vector && compare);

    vector->compare = compare;
}

void bvector_print(const BridgeVector *vector)
{
    bvector_print_len(vector, 512);
}

void bvector_print_len(const BridgeVector *vector, int len)
{
    assert(vector);

    BridgeNode *node = NULL;
    char *dst = (char *)malloc(len + 1);
    dst[0] = '\0';

    for (int i = 0; i < vector->size; ++i) {
        node = (BridgeNode *)(vector->elements + i * vector->esize);

        if (vector->tostr) {
            vector->tostr(bnode_to_object(node), dst, len);
        } else {
            bnode_tostr(node, dst, len);
        }

        printf("%s ", dst);
    }

    free(dst);
}

int bvector_size(BridgeVector *vector) 
{
    return vector->size;
}


