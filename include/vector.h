#pragma once

typedef struct BridgeVector BridgeVector;
typedef void(*BridgeVectorPrint)(void *);

extern BridgeVector *bvector_create();
extern void bvector_destroy(BridgeVector *vector);

extern void bvector_append_ival(BridgeVector *vector, long long ival);
extern void bvector_append_dval(BridgeVector *vector, long double dval);
extern void bvector_append_sval(BridgeVector *vector, const char *sval);
extern void bvector_append_pval(BridgeVector *vector, void *pval);

extern long long bvector_fetch_ival(BridgeVector *vector, int index);
extern long double bvector_fetch_dval(BridgeVector *vector, int index);
extern const char *bvector_fetch_sval(BridgeVector *vector, int index);
extern void *bvector_fetch_pval(BridgeVector *vector, int index);

extern void bvector_modify_ival(BridgeVector *vector, int index, long long ival);
extern void bvector_modify_dval(BridgeVector *vector, int index, long double dval);
extern void bvector_modify_sval(BridgeVector *vector, int index, const char *sval);
extern void bvector_modify_pval(BridgeVector *vector, int index, void *pval);

extern void bvector_print_normal(const BridgeVector *vector);
extern void bvector_print_callback(const BridgeVector *vector, BridgeVectorPrint print);

extern int bvector_size(BridgeVector *vector);


