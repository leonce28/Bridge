#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "node.h"

BridgeNode *bnode_create_ival(long long ival)
{
    BridgeNode *node = (BridgeNode *)malloc(sizeof(BridgeNode));
    
    assert(node);

    node->type = B_Integer;
    node->val.ival = ival;

    return node;
}

BridgeNode *bnode_create_dval(long double dval)
{
    BridgeNode *node = (BridgeNode *)malloc(sizeof(BridgeNode));
    
    assert(node);

    node->type = B_Decimal;
    node->val.dval = dval;

    return node;
}

BridgeNode *bnode_create_sval(const char *sval)
{
    assert(sval);

    int len = strlen(sval);
    BridgeNode *node = (BridgeNode *)malloc(sizeof(BridgeNode));
    
    assert(node);

    node->type = B_String;
    node->val.sval = malloc(len + 1);;

    assert(node->val.sval);

    strncpy(node->val.sval, sval, len);

    node->val.sval[len] = '\0';

    return node;
}

BridgeNode *bnode_create_pval(void *pval)
{
    assert(pval);

    BridgeNode *node = (BridgeNode *)malloc(sizeof(BridgeNode));
    
    assert(node);

    node->type = B_Pointer;
    node->val.pval = pval;

    return node;
}
