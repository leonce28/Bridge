#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "list.h"

struct BridgeList {
    int type;
    BridgeNode *head;
    BridgeNode *tail;
    size_t size;
};

BridgeList *blist_create() {
    BridgeList *list = malloc(sizeof(BridgeList));

    if (!list) {
        return NULL;
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->type = B_Invalid;
    return list;
}

void blist_destroy(BridgeList *list) {
    BridgeNode *next = NULL;
    BridgeNode *node = list->head;

    while (node) {
        next = node->next;
        free(node);
        node = next;
    }

    free(list);
}

void blist_push_front(BridgeList *list, BridgeNode *node) {

    assert(list && node);

    if (list->type == B_Invalid) {
        list->type = node->type;
    }

    assert(list->type == node->type);

    node->next = list->head;

    if (!list->tail) {
        list->tail = node;
    }

    list->head = node;
    list->size++;
}

void blist_push_back(BridgeList *list, BridgeNode *node) 
{
    assert(list && node);

    if (list->type == B_Invalid) {
        list->type = node->type;
    }

    assert(list->type == node->type);

    node->next = NULL;

    if (list->tail) {
        list->tail->next = node;
    } else {
        list->head = node;
    }

    list->tail = node;
    list->size++;
}

void blist_push_front_ival(BridgeList *list, long long ival)
{
    blist_push_front(list, bnode_create_ival(ival));
}

void blist_push_front_dval(BridgeList *list, long double dval)
{
    blist_push_front(list, bnode_create_dval(dval));
}

void blist_push_front_sval(BridgeList *list, const char *sval)
{
    blist_push_front(list, bnode_create_sval(sval));
}

void blist_push_front_pval(BridgeList *list, void *pval)
{
    blist_push_front(list, bnode_create_pval(pval));
}

void blist_push_back_ival(BridgeList *list, long long ival)
{
    blist_push_back(list, bnode_create_ival(ival));
}

void blist_push_back_dval(BridgeList *list, long double dval)
{
    blist_push_back(list, bnode_create_dval(dval));
}

void blist_push_back_sval(BridgeList *list, const char *sval)
{
    blist_push_back(list, bnode_create_sval(sval));
}

void blist_push_back_pval(BridgeList *list, void *pval)
{
    blist_push_back(list, bnode_create_pval(pval));
}

void blist_pop_front(BridgeList *list) 
{
    assert(list);

    if (!list->head) {
        return;
    }

    BridgeNode *node = list->head;
    list->head = node->next;

    if (!list->head) {
        list->tail = NULL;
    }

    free(node);
    list->size--;
}

void blist_pop_back(BridgeList *list) 
{
    assert(list);

    if (!list->tail) {
        return;
    }

    if (list->head == list->tail) {
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
        list->size = 0;
        return;
    }

    BridgeNode *node = list->head;
    while (node->next != list->tail) {
        node = node->next;
    }

    free(list->tail);

    node->next = NULL;
    list->tail = node;
    list->size--;
}

void blist_print_normal(const BridgeList *list)
{
    assert(list);

    BridgeNode *node = list->head;

    while (node) {
        switch (node->type) {
            case B_Integer:
                printf("%lld ", node->val.ival);
                break;
            case B_Decimal:
                printf("%Lf ", node->val.dval);
                break;
            case B_String:
                printf("%s ", node->val.sval);
                break;
            case B_Pointer:
                printf("%p ", node->val.pval);
                break;
        }

        node = node->next;
    }
}

void blist_print_callback(const BridgeList *list, BridgeListPrint print)
{
    BridgeNode *node = list->head;
    while (node) {
        print(node->val.pval);
        node = node->next;
    }
}
