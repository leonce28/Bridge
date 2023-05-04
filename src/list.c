#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "list.h"
#include "node.h"

typedef struct BridgeListNode {
    BridgeNode *value;
    struct BridgeListNode *next;
} BridgeListNode;

struct BridgeList {
    int type;
    size_t size;
    BridgeListNode *head;
    BridgeListNode *tail;
};

BridgeList *blist_create() 
{
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
    BridgeListNode *next = NULL;
    BridgeListNode *node = list->head;

    while (node) {
        next = node->next;
        if (node->value) {
            free(node->value);
        }
        free(node);
        node = next;
    }

    free(list);
}

void blist_push_front(BridgeList *list, BridgeNode *node) 
{
    assert(list && node);

    if (list->type == B_Invalid) {
        list->type = node->type;
    }

    assert(list->type == node->type);

    BridgeListNode *lnode = malloc(sizeof(BridgeListNode));

    assert(lnode);

    lnode->value = node;
    lnode->next = list->head;

    if (!list->tail) {
        list->tail = lnode;
    }

    list->head = lnode;
    list->size++;
}

void blist_push_back(BridgeList *list, BridgeNode *node) 
{
    assert(list && node);

    if (list->type == B_Invalid) {
        list->type = node->type;
    }

    assert(list->type == node->type);

    BridgeListNode *lnode = malloc(sizeof(BridgeListNode));

    assert(lnode);

    lnode->value = node;
    lnode->next = NULL;

    if (list->tail) {
        list->tail->next = lnode;
    } else {
        list->head = lnode;
    }

    list->tail = lnode;
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

    BridgeListNode *lnode = list->head;
    list->head = lnode->next;

    if (!list->head) {
        list->tail = NULL;
    }

    if (lnode->value) {
        free(lnode->value);
    }
    free(lnode);
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

    BridgeListNode *lnode = list->head;
    while (lnode->next != list->tail) {
        lnode = lnode->next;
    }

    if (list->tail->value) {
        free(list->tail->value);
    }
    free(list->tail);

    lnode->next = NULL;
    list->tail = lnode;
    list->size--;
}

void blist_print_normal(const BridgeList *list)
{
    assert(list);

    BridgeListNode *lnode = list->head;

    while (lnode && lnode->value) {
        switch (lnode->value->type) {
            case B_Integer:
                printf("%lld ", lnode->value->val.ival);
                break;
            case B_Decimal:
                printf("%Lf ", lnode->value->val.dval);
                break;
            case B_String:
                printf("%s ", lnode->value->val.sval);
                break;
            case B_Pointer:
                printf("%p ", lnode->value->val.pval);
                break;
        }

        lnode = lnode->next;
    }
}

void blist_print_callback(const BridgeList *list, BridgeListPrint print)
{
    assert(list && print);

    BridgeListNode *node = list->head;
    while (node && node->value) {
        print(node->value->val.pval);
        node = node->next;
    }
}
