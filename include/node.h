#pragma once

#ifndef bool
#define bool    short
#endif

#ifndef true
#define true    (1)
#endif

#ifndef false
#define false   (0)
#endif

#ifndef nullptr
#define nullptr (NULL)
#endif

typedef enum BridgeNodeType {
    B_Invalid,
    B_Integer,
    B_Decimal,
    B_String,
    B_Object,
    B_Maximum,
} BridgeNodeType;

typedef struct BridgeNode BridgeNode;

extern BridgeNode *bnode_integer(long long ival);
extern BridgeNode *bnode_decimal(long double dval);
extern BridgeNode *bnode_string(const char *sval);
extern BridgeNode *bnode_object(void *oval);

extern long long bnode_to_integer(const BridgeNode *node);
extern long double bnode_to_decimal(const BridgeNode *node);
extern const char *bnode_to_string(const BridgeNode *node);
extern const void *bnode_to_object(const BridgeNode *node);

extern void bnode_set_integer(BridgeNode *node, long long ival);
extern void bnode_set_decimal(BridgeNode *node, long double dval);
extern void bnode_set_string(BridgeNode *node, const char *sval);
extern void *bnode_set_object(BridgeNode *node, void *oval);

extern int bnode_size();
extern int bnode_length(const BridgeNode *node);
extern void bnode_tostr(const BridgeNode *node, char *dst, int max);
extern BridgeNodeType bnode_type(const BridgeNode *node);

extern bool bnode_is_equal(const BridgeNode *node1, const BridgeNode *node2);
extern bool bnode_not_equal(const BridgeNode *node1, const BridgeNode *node2);
