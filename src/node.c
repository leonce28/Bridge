#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "node.h"

struct BridgeNode {
    int type;
    int length;
    union {
        long long ival;
        long double dval;
        char *sval;
        void *oval;
    } val;
};

BridgeNode *bnode_create()
{
    BridgeNode *node = (BridgeNode *)malloc(sizeof(BridgeNode));
    assert(node);

    return node;
}

BridgeNode *bnode_integer(long long ival)
{
    BridgeNode *node = bnode_create();
    
    node->type = B_Integer;
    node->val.ival = ival;

    return node;
}

BridgeNode *bnode_decimal(long double dval)
{
    BridgeNode *node = bnode_create();
    
    node->type = B_Decimal;
    node->val.dval = dval;

    return node;
}

BridgeNode *bnode_string(const char *sval)
{
    assert(sval);

    int len = strlen(sval);
    BridgeNode *node = bnode_create();
    
    node->type = B_String;
    node->val.sval = malloc(len + 1);;

    assert(node->val.sval);

    strncpy(node->val.sval, sval, len);

    node->val.sval[len] = '\0';

    return node;
}

BridgeNode *bnode_object(void *oval)
{
    assert(oval);

    BridgeNode *node = bnode_create();
    
    node->type = B_Object;
    node->val.oval = oval;

    return node;
}

BridgeNode *bnode_object2(const void *oval, int length)
{
    assert(oval && length > 0);

    BridgeNode *node = bnode_create();
    
    node->length = length;
    node->type = B_Object;

    memcpy(node->val.oval, oval, length);

    return node;
}

long long bnode_to_integer(const BridgeNode *node)
{
     assert(node && node->type == B_Integer);

     return node->val.ival;
}

long double bnode_to_decimal(const BridgeNode *node)
{
     assert(node && node->type == B_Decimal);

     return node->val.dval;
}

const char *bnode_to_string(const BridgeNode *node)
{
     assert(node && node->type == B_String);

     return node->val.sval;
}

const void *bnode_to_object(const BridgeNode *node)
{
     assert(node && node->type == B_Object);

     return node->val.oval;
}

void bnode_set_integer(BridgeNode *node, long long ival)
{
    assert(node && node->type == B_Integer);

    node->val.ival = ival;
}

void bnode_set_decimal(BridgeNode *node, long double dval)
{
    assert(node && node->type == B_Decimal);

    node->val.dval = dval;
}

void bnode_set_string(BridgeNode *node, const char *sval)
{
    assert(node && node->type == B_String && sval);

    int len = strlen(sval);
    
    if (len > node->length) {
        node->val.sval = realloc(node->val.sval, len + 1);
        assert(node->val.sval);
        node->length = len;
    }

    strncpy(node->val.sval, sval, len);
    node->val.sval[len] = '\0';
}

void bnode_set_object(BridgeNode *node, const void *oval, int length)
{
    assert(node && node->type == B_Object && oval);

    memcpy(node->val.oval, oval, length);
}

int bnode_size()
{
    return sizeof(BridgeNode);
}

int bnode_length(const BridgeNode *node)
{
    return node->length;
}

BridgeNodeType bnode_type(const BridgeNode *node)
{
    return node->type;
}

void bnode_copy(BridgeNode *dst, const BridgeNode *src)
{
    assert(dst && src);
    
    dst->type = src->type;
    dst->length = src->length;

    memcpy(dst->val.oval, src->val.oval, dst->length);
}

BridgeNode *bnode_create1(const BridgeNode *node)
{
    BridgeNode *dst = bnode_create();

    bnode_copy(dst, node);

    return dst;
}

bool bnode_is_equal(const BridgeNode *node1, const BridgeNode *node2)
{
    return node1->type == node2->type;
}

bool bnode_not_equal(const BridgeNode *node1, const BridgeNode *node2)
{
    return bnode_is_equal(node1, node2);
}

void bnode_transfer(BridgeNode *dst, BridgeNode *src)
{
    assert(dst && src && dst->type == src->type);

    void *temp = src->val.oval;
    int length = src->length;

    src->length = dst->length;
    src->val.oval = dst->val.oval;

    dst->length = length;
    dst->val.oval = temp;
}

