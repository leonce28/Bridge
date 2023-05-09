#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "list.h"

typedef struct BridgeListNode {
    BridgeNode *value;
    struct BridgeListNode *next;
} BridgeListNode;

struct BridgeList {
    int size;
    BridgeNodeType type;
    BridgeListNode *head;
    BridgeListNode *tail;
};

BridgeList *blist_create(BridgeNodeType type) 
{
    BridgeList *list = malloc(sizeof(BridgeList));

    if (!list) {
        return NULL;
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->type = type;
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

void blist_push_front(BridgeList *list, const BridgeNode *node) 
{
    assert(list && node && list->type == bnode_type(node));

    BridgeListNode *lnode = malloc(sizeof(BridgeListNode));

    assert(lnode);

    lnode->value = bnode_create1(node);
    lnode->next = list->head;

    if (!list->tail) {
        list->tail = lnode;
    }

    list->head = lnode;
    list->size++;
}

void blist_push_back(BridgeList *list, const BridgeNode *node)
{
    assert(list && node && list->type == bnode_type(node));

    BridgeListNode *lnode = malloc(sizeof(BridgeListNode));

    assert(lnode);

    lnode->value = bnode_create1(node);
    lnode->next = NULL;

    if (list->tail) {
        list->tail->next = lnode;
    } else {
        list->head = lnode;
    }

    list->tail = lnode;
    list->size++;
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
        switch (bnode_type(lnode->value)) {
            case B_Integer:
                printf("%lld ", bnode_to_integer(lnode->value));
                break;
            case B_Decimal:
                printf("%Lf ", bnode_to_decimal(lnode->value));
                break;
            case B_String:
                printf("%s ", bnode_to_string(lnode->value));
                break;
            case B_Object:
                printf("%p ", bnode_to_object(lnode->value));
                break;
            case B_Invalid:
            case B_Maximum:
            default:
                break;
        }
        lnode = lnode->next;
    }
}

void blist_print_callback(const BridgeList *list, BridgeListPrint print)
{
    assert(list && print);

    BridgeListNode *lnode = list->head;
    while (lnode && lnode->value) {
        print(bnode_to_object(lnode->value));
        lnode = lnode->next;
    }
}
