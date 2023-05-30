#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "node.h"

typedef enum BridgeNodeType {
    B_Invalid,
    B_Integer,
    B_Decimal,
    B_String,
    B_Object,
    B_Maximum,
} BridgeNodeType;

struct BridgeNode {
    int type;
    int extra;
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
    
    node->extra = len;
    node->type = B_String;
    node->val.sval = malloc(len + 1);

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

const void *bnode_to_void(const BridgeNode *node)
{
     assert(node);

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
    assert(node && node->type == B_String&& sval);

    int len = strlen(sval);
    
    if (len > node->extra) {
        node->val.sval = realloc(node->val.sval, len + 1);
    }

    assert(node->val.sval);

    strncpy(node->val.sval, sval, len);
    node->val.sval[len] = '\0';
}

void *bnode_set_object(BridgeNode *node, void *oval)
{
    assert(node && node->type == B_Object && oval);

    void *del = node->val.oval;
    
    node->val.oval = oval;

    return del;
}

int bnode_size()
{
    return sizeof(BridgeNode);
}

unsigned int bnode_hash_string(const char *string)
{
    unsigned char c;
    unsigned int i, len;
    unsigned int hash = 5381;

    while (*string) {

        c = (unsigned char)*string;
        if ((c & 0x80) == 0) {
            len = 1;
        } else if ((c & 0xE0) == 0xC0) {
            len = 2;
        } else if ((c & 0xF0) == 0xE0) {
            len = 3;
        } else if ((c & 0xF8) == 0xF0) {
            len = 4;
        } else {
            len = 0;
        }

        for (i = 0; i < len; i++) {
            hash = ((hash << 5) + hash) + (unsigned int)*string;
            string++;
        }
    }

    return hash;
}

unsigned int bnode_hash(const BridgeNode *node)
{
    assert(node);

    unsigned int hash = 0;

    switch (node->type) {
        case B_Integer:
            hash = node->val.ival;
            break;
        case B_Decimal:
            hash = (unsigned int)(node->val.dval * 31);
            break;
        case B_String:
            hash = bnode_hash_string(node->val.sval);
            break;
        case B_Object:
            hash = sizeof(node->val.oval);
            break;
        default:
            break;
    }

    return hash;
}

void bnode_tostr(const BridgeNode *node, char *dst, int max)
{
    assert(node && dst && max > 0);

    switch (node->type) {
        case B_Integer:
            snprintf(dst, max, "%lld", bnode_to_integer(node));
            break;
        case B_Decimal:
            snprintf(dst, max, "%Lf", bnode_to_decimal(node));
            break;
        case B_String:
            snprintf(dst, max, "%s", bnode_to_string(node));
            break;
        case B_Object:
            snprintf(dst, max, "%p", bnode_to_object(node));
            break;
        default:
            break;
    }
}

BridgeNodeType bnode_type(const BridgeNode *node)
{
    return node->type;
}

bool bnode_equal(const BridgeNode *node1, const BridgeNode *node2)
{
    return node1->type == node2->type;
}

bool bnode_is_integer(BridgeNode *node)
{
    return node->type == B_Integer;
}

bool bnode_is_decimal(BridgeNode *node)
{
    return node->type == B_Decimal;

}

bool bnode_is_string(BridgeNode *node)
{
    return node->type == B_String;
}

bool bnode_is_object(BridgeNode *node)
{
    return node->type == B_Object;
}