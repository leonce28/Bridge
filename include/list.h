#pragma once

#include "node.h"

typedef struct BridgeList BridgeList;
typedef void(*BridgeListPrint)(const void *);

extern BridgeList *blist_create(BridgeNodeType type);
extern void blist_destroy(BridgeList *list);

extern void blist_push_front(BridgeList *list, const BridgeNode *node);
extern void blist_push_back(BridgeList *list, const BridgeNode *node);

extern void blist_pop_front(BridgeList *list);
extern void blist_pop_back(BridgeList *list);

extern void blist_print_normal(const BridgeList *list);
extern void blist_print_callback(const BridgeList *list, BridgeListPrint print);

// extern BridgeNode *blist_node_front(const BridgeList *list);
// extern BridgeNode *blist_node_back(const BridgeList *list);
// extern BridgeNode *blist_node_next(const BridgeNode *node);

// extern void *blist_node_data(const BridgeNode *node);