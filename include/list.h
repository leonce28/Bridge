#pragma once

typedef struct BridgeList BridgeList;
typedef void(*BridgeListPrint)(void *);

extern BridgeList *blist_create();
extern void blist_destroy(BridgeList *list);

extern void blist_push_front_ival(BridgeList *list, long long ival);
extern void blist_push_front_dval(BridgeList *list, long double dval);
extern void blist_push_front_sval(BridgeList *list, const char *sval);
extern void blist_push_front_pval(BridgeList *list, void *pval);

extern void blist_push_back_ival(BridgeList *list, long long ival);
extern void blist_push_back_dval(BridgeList *list, long double dval);
extern void blist_push_back_sval(BridgeList *list, const char *sval);
extern void blist_push_back_pval(BridgeList *list, void *pval);

extern void blist_pop_front(BridgeList *list);
extern void blist_pop_back(BridgeList *list);

extern void blist_print_normal(const BridgeList *list);
extern void blist_print_callback(const BridgeList *list, BridgeListPrint print);

// extern BridgeNode *blist_node_front(const BridgeList *list);
// extern BridgeNode *blist_node_back(const BridgeList *list);
// extern BridgeNode *blist_node_next(const BridgeNode *node);

// extern void *blist_node_data(const BridgeNode *node);