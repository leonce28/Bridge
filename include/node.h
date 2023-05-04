#pragma once

enum BridgeNodeType {
    B_Invalid,
    B_Integer,
    B_Decimal,
    B_String,
    B_Pointer,
};

typedef struct BridgeNode {
    int type;
    union {
        long long ival;
        long double dval;
        char *sval;
        void *pval;
    } val;
    struct BridgeNode *next;
} BridgeNode;

extern BridgeNode *bnode_create_ival(long long ival);
extern BridgeNode *bnode_create_dval(long double dval);
extern BridgeNode *bnode_create_sval(const char *sval);
extern BridgeNode *bnode_create_pval(void *pval);