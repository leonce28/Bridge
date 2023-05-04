#include <stdio.h>
#include "vector.h"
#include "test.h"

void integer_test()
{
    BridgeVector *vector = bvector_create();

    if (!vector) {
        return;
    }

    bvector_append_ival(vector, 1);
    bvector_append_ival(vector, 2);
    bvector_append_ival(vector, 3);
    bvector_append_ival(vector, 4);
    bvector_append_ival(vector, 5);
    bvector_append_ival(vector, 6);

    bvector_print_normal(vector);
    printf("\n");

    bvector_modify_ival(vector, 1, 11);
    bvector_modify_ival(vector, 3, 33);
    bvector_modify_ival(vector, 4, 44);

    bvector_print_normal(vector);
    printf("\n");

    printf("fetch index[%d] value: %lld from vector.\n", 1, bvector_fetch_ival(vector, 1));
    printf("fetch index[%d] value: %lld from vector.\n", 4, bvector_fetch_ival(vector, 4));

    bvector_destroy(vector);
}

void decimal_test()
{
    BridgeVector *vector = bvector_create();

    if (!vector) {
        return;
    }

    bvector_append_dval(vector, 1.1);
    bvector_append_dval(vector, 2.2);
    bvector_append_dval(vector, 3.3);
    bvector_append_dval(vector, 4.4);
    bvector_append_dval(vector, 5.5);
    bvector_append_dval(vector, 6.6);

    bvector_print_normal(vector);

    printf("\n");

    bvector_modify_dval(vector, 1, 11.11);
    bvector_modify_dval(vector, 3, 33.33);
    bvector_modify_dval(vector, 4, 44.44);

    bvector_print_normal(vector);
    printf("\n");

    printf("fetch index[%d] value: %Lf from vector.\n", 1, bvector_fetch_dval(vector, 1));
    printf("fetch index[%d] value: %Lf from vector.\n", 4, bvector_fetch_dval(vector, 4));

    bvector_destroy(vector);
}

void string_test()
{
    BridgeVector *vector = bvector_create();

    if (!vector) {
        return;
    }

    bvector_append_sval(vector, "string1");
    bvector_append_sval(vector, "string2");
    bvector_append_sval(vector, "string3");
    bvector_append_sval(vector, "string4");
    bvector_append_sval(vector, "string5");
    bvector_append_sval(vector, "string6");

    bvector_print_normal(vector);

    printf("\n");

    bvector_modify_sval(vector, 1, "str111");
    bvector_modify_sval(vector, 3, "str333");
    bvector_modify_sval(vector, 4, "str444");

    bvector_print_normal(vector);
    printf("\n");

    printf("fetch index[%d] value: %s from vector.\n", 1, bvector_fetch_sval(vector, 1));
    printf("fetch index[%d] value: %s from vector.\n", 4, bvector_fetch_sval(vector, 4));

    bvector_destroy(vector);
}

void pointer_test()
{
    BridgeVector *vector = bvector_create();

    if (!vector) {
        return;
    }

    bvector_append_pval(vector, student_create(1, 18, "zhangsan"));
    bvector_append_pval(vector, student_create(2, 27, "lisi"));
    bvector_append_pval(vector, student_create(3, 36, "wangwu"));
    bvector_append_pval(vector, student_create(4, 45, "liuliu"));
    bvector_append_pval(vector, student_create(5, 54, "qiqi"));
    bvector_append_pval(vector, student_create(6, 63, "laoba"));

    bvector_print_callback(vector, student_print);

    printf("\n");

    bvector_modify_pval(vector, 1, student_create(1, 81, "zangshan"));
    bvector_modify_pval(vector, 3, student_create(3, 63, "wawuwu"));
    bvector_modify_pval(vector, 4, student_create(4, 54, "niuniu"));

    bvector_print_callback(vector, student_print);

    printf("\n");

    student_print(bvector_fetch_pval(vector, 1));
    student_print(bvector_fetch_pval(vector, 4));

    printf("\n");

    bvector_destroy(vector);
}

int main() {
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