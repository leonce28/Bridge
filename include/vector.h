#pragma once

#include "node.h"

typedef struct BridgeVector BridgeVector;
typedef void(*BridgeVectorPrint)(const void *);

extern BridgeVector *bvector_create(BridgeNodeType type);
extern void bvector_destroy(BridgeVector *vector);

extern void bvector_append(BridgeVector *vector, const BridgeNode *node);
extern BridgeNode *bvector_fetch(BridgeVector *vector, int index);

extern void bvector_set_integer(BridgeVector *vector, int index, long long ival);
extern void bvector_set_decimal(BridgeVector *vector, int index, long double dval);
extern void bvector_set_string(BridgeVector *vector, int index, const char *sval);
extern void bvector_set_object(BridgeVector *vector, int index, const void *oval, int length);

extern void bvector_print_normal(const BridgeVector *vector);
extern void bvector_print_callback(const BridgeVector *vector, BridgeVectorPrint print);

extern int bvector_size(BridgeVector *vector);


