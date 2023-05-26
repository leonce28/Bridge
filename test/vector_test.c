#include <stdio.h>
#include "vector.h"
#include "test.h"

void integer_test()
{
    BridgeVector *vector = bvector_create();

    if (!vector) {
        return;
    }

    for (int i = 0; i < 10; ++i) {
        bvector_append(vector, bnode_integer(i));
    }

    bvector_print(vector);
    printf("\n");

    bnode_set_integer(bvector_fetch(vector, 1), 11);
    bnode_set_integer(bvector_fetch(vector, 3), 33);
    bnode_set_integer(bvector_fetch(vector, 4), 44);

    bvector_print(vector);
    printf("\n");

    printf("fetch index[%d] value: %lld from vector.\n", 1, bnode_to_integer(bvector_fetch(vector, 1)));
    printf("fetch index[%d] value: %lld from vector.\n", 4, bnode_to_integer(bvector_fetch(vector, 4)));

    bvector_destroy(vector);
}

void decimal_test()
{
    BridgeVector *vector = bvector_create();

    if (!vector) {
        return;
    }

    float val = 1.142;
    for (int i = 0; i < 10; ++i) {
        bvector_append(vector, bnode_decimal(i));
        val += 1.131;
    }

    bvector_print(vector);
    printf("\n");

    bnode_set_decimal(bvector_fetch(vector, 1), 141.121);
    bnode_set_decimal(bvector_fetch(vector, 3), 323.383);
    bnode_set_decimal(bvector_fetch(vector, 4), 414.474);

    bvector_print(vector);
    printf("\n");

    printf("fetch index[%d] value: %Lf from vector.\n", 1, bnode_to_decimal(bvector_fetch(vector, 1)));
    printf("fetch index[%d] value: %Lf from vector.\n", 4, bnode_to_decimal(bvector_fetch(vector, 4)));

    bvector_destroy(vector);
}

void string_test()
{
    BridgeVector *vector = bvector_create();

    if (!vector) {
        return;
    }

    bvector_append(vector, bnode_string("string1"));
    bvector_append(vector, bnode_string("string2"));
    bvector_append(vector, bnode_string("string3"));
    bvector_append(vector, bnode_string("string4"));
    bvector_append(vector, bnode_string("string5"));
    bvector_append(vector, bnode_string("string6"));

    bvector_print(vector);
    printf("\n");

    bnode_set_string(bvector_fetch(vector, 1), "str111");
    bnode_set_string(bvector_fetch(vector, 3), "str333");
    bnode_set_string(bvector_fetch(vector, 4), "str444");

    bvector_print(vector);
    printf("\n");

    printf("fetch index[%d] value: %s from vector.\n", 1, bnode_to_string(bvector_fetch(vector, 1)));
    printf("fetch index[%d] value: %s from vector.\n", 4, bnode_to_string(bvector_fetch(vector, 4)));

    bvector_destroy(vector);
}

void object_test()
{
    char tostr[512] = { 0 };
    const void *data = NULL;

    BridgeVector *vector = bvector_create();

    if (!vector) {
        return;
    }

    bvector_udf_free(vector, student_free);
    bvector_udf_tostr(vector, student_tostr);
    bvector_udf_compare(vector, student_compare);

    char name[20];
    for (int i = 0; i < 10; ++i) {
        snprintf(name, 20, "name%d", i);
        bvector_append(vector, bnode_object(student_create(i + 1, 18 + i * 2, name)));
    }

    bvector_print(vector);
    printf("\n");

    bvector_set_object(vector, 1, bnode_object(student_create(100, 90, "name101")));
    bvector_set_object(vector, 3, bnode_object(student_create(101, 94, "name102")));
    bvector_set_object(vector, 4, bnode_object(student_create(102, 98, "name103")));

    bvector_print(vector);
    printf("\n");

    student_tostr(bnode_to_object(bvector_fetch(vector, 1)), tostr, 512);
    printf("fetch index[%d] value: %s from vector.\n", 1, tostr);

    student_tostr(bnode_to_object(bvector_fetch(vector, 4)), tostr, 512);
    printf("fetch index[%d] value: %s from vector.\n", 4, tostr);

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
    object_test();
    printf("---------------------------\n");
    return 0;
}