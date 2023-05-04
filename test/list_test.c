#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

typedef struct Student {
    int no;
    int age;
    char name[20];
} Student;


Student *student_create(int no, int age, const char *name)
{
    int len = 0;
    Student *stu = (Student *)malloc(sizeof(Student));

    stu->no = no;
    stu->age = age;

    if (name) {
        len = strlen(name) > 19 ? strlen(name) : 19;
        strncpy(stu->name, name, len);
    } 

    stu->name[len] = '\0';
    return stu;
}

void student_print(void *data)
{
    if (!data) {
        return;
    }

    Student *stu = (Student *)data;
    printf("(%d, %d, %s) ", stu->no, stu->age, stu->name);
}

void integer_test()
{
    BridgeList *list = blist_create();

    if (!list) {
        return;
    }

    blist_push_back_ival(list, 1);
    blist_push_back_ival(list, 2);
    blist_push_front_ival(list, 3);
    blist_push_front_ival(list, 4);
    blist_push_back_ival(list, 5);
    blist_push_front_ival(list, 6);

    blist_print_normal(list);

    printf("\n");

    blist_pop_front(list);
    blist_pop_front(list);
    blist_pop_back(list);
    blist_pop_back(list);
    blist_pop_front(list);

    blist_print_normal(list);

    blist_destroy(list);

    printf("\n");
}

void decimal_test()
{
    BridgeList *list = blist_create();

    if (!list) {
        return;
    }

    blist_push_back_dval(list, 1.1);
    blist_push_back_dval(list, 2.2);
    blist_push_front_dval(list, 3.3);
    blist_push_front_dval(list, 4.4);
    blist_push_back_dval(list, 5.5);
    blist_push_front_dval(list, 6.6);

    blist_print_normal(list);

    printf("\n");

    blist_pop_front(list);
    blist_pop_front(list);
    blist_pop_back(list);
    blist_pop_back(list);
    blist_pop_front(list);

    blist_print_normal(list);

    blist_destroy(list);
    printf("\n");
}

void string_test()
{
    BridgeList *list = blist_create();

    if (!list) {
        return;
    }

    blist_push_back_sval(list, "string1");
    blist_push_back_sval(list, "string2");
    blist_push_front_sval(list, "string3");
    blist_push_front_sval(list, "string4");
    blist_push_back_sval(list, "string5");
    blist_push_front_sval(list, "string6");

    blist_print_normal(list);

    printf("\n");

    blist_pop_front(list);
    blist_pop_front(list);
    blist_pop_back(list);
    blist_pop_back(list);
    blist_pop_front(list);

    blist_print_normal(list);

    blist_destroy(list);
    printf("\n");
}

void pointer_test()
{
    BridgeList *list = blist_create();

    if (!list) {
        return;
    }
    
    blist_push_back_pval(list, student_create(1, 18, "zhangsan"));
    blist_push_back_pval(list, student_create(2, 27, "lisi"));
    blist_push_front_pval(list, student_create(3, 36, "wangwu"));
    blist_push_front_pval(list, student_create(4, 45, "liuliu"));
    blist_push_back_pval(list, student_create(5, 54, "qiqi"));
    blist_push_front_pval(list, student_create(6, 63, "laoba"));

    blist_print_callback(list, student_print);

    printf("\n");

    blist_pop_front(list);
    blist_pop_front(list);
    blist_pop_back(list);
    blist_pop_back(list);
    blist_pop_front(list);

    blist_print_callback(list, student_print);

    blist_destroy(list);
    printf("\n");
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
    pointer_test();
    printf("---------------------------\n");
    return 0;
}