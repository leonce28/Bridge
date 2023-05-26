#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "test.h"

void integer_test()
{
    BridgeList *list = blist_create();

    if (!list) {
        return;
    }

    blist_push_back(list, bnode_integer(1));
    blist_push_back(list, bnode_integer(2));
    blist_push_front(list, bnode_integer(3));
    blist_push_front(list, bnode_integer(4));
    blist_push_back(list, bnode_integer(5));
    blist_push_front(list, bnode_integer(6));

    blist_print(list);
    printf("\n");

    blist_pop_front(list);
    blist_pop_front(list);
    blist_pop_back(list);
    blist_pop_back(list);
    blist_pop_front(list);

    blist_print(list);
    printf("\n");

    blist_destroy(list);
}

void decimal_test()
{
    BridgeList *list = blist_create();

    if (!list) {
        return;
    }

    blist_push_back(list, bnode_decimal(1.1));
    blist_push_back(list, bnode_decimal(2.2));
    blist_push_front(list, bnode_decimal(3.3));
    blist_push_front(list, bnode_decimal(4.4));
    blist_push_back(list, bnode_decimal(5.5));
    blist_push_front(list, bnode_decimal(6.6));

    blist_print(list);
    printf("\n");

    blist_pop_front(list);
    blist_pop_front(list);
    blist_pop_back(list);
    blist_pop_back(list);
    blist_pop_front(list);

    blist_print(list);
    printf("\n");

    blist_destroy(list);
}

void string_test()
{
    BridgeList *list = blist_create();

    if (!list) {
        return;
    }

    blist_push_back(list, bnode_string("string1"));
    blist_push_back(list, bnode_string("string2"));
    blist_push_front(list, bnode_string("string3"));
    blist_push_front(list, bnode_string("string4"));
    blist_push_back(list, bnode_string("string5"));
    blist_push_front(list, bnode_string("string6"));

    blist_print(list);
    printf("\n");

    blist_pop_front(list);
    blist_pop_front(list);
    blist_pop_back(list);
    blist_pop_back(list);
    blist_pop_front(list);

    blist_print(list);
    printf("\n");

    blist_destroy(list);
}

void object_test()
{
    BridgeList *list = blist_create();

    if (!list) {
        return;
    }

    blist_udf_free(list, student_free);
    blist_udf_tostr(list, student_tostr);
    blist_udf_compare(list, student_compare);

    blist_push_back(list, bnode_object(student_create(1, 18, "zhangsan")));
    blist_push_back(list, bnode_object(student_create(2, 27, "lisi")));
    blist_push_front(list, bnode_object(student_create(3, 36, "wangwu")));
    blist_push_front(list, bnode_object(student_create(4, 45, "liuliu")));
    blist_push_back(list, bnode_object(student_create(5, 54, "qiqi")));
    blist_push_front(list, bnode_object(student_create(6, 63, "laoba")));

    blist_print(list);
    printf("\n");

    blist_pop_front(list);
    blist_pop_front(list);
    blist_pop_back(list);
    blist_pop_back(list);
    blist_pop_front(list);

    blist_print(list);
    printf("\n");

    blist_destroy(list);
}

int main(int argc, char *args[]) 
{
    printf("---------------------------\n");
    integer_test();
    printf("---------------------------\n");
    decimal_test();
    printf("---------------------------\n");
    string_test();
    printf("---------------------------\n");
    object_test();
    printf("---------------------------\n");
    return 0;
}