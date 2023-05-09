#include <stdio.h>
#include "vector.h"
#include "test.h"

void integer_test()
{
    BridgeVector *vector = bvector_create(B_Integer);

    if (!vector) {
        return;
    }

    for (int i = 0; i < 10; ++i) {
        bvector_append(vector, bnode_integer(i));
    }

    bvector_print_normal(vector);
    printf("\n");

    bnode_set_integer(bvector_fetch(vector, 1), 11);
    bnode_set_integer(bvector_fetch(vector, 3), 33);
    bnode_set_integer(bvector_fetch(vector, 4), 44);

    bvector_print_normal(vector);
    printf("\n");

    printf("fetch index[%d] value: %lld from vector.\n", 1, bnode_to_integer(bvector_fetch(vector, 1)));
    printf("fetch index[%d] value: %lld from vector.\n", 4, bnode_to_integer(bvector_fetch(vector, 4)));

    bvector_destroy(vector);
}

void decimal_test()
{
    BridgeVector *vector = bvector_create(B_Decimal);

    if (!vector) {
        return;
    }

    float val = 1.142;
    for (int i = 0; i < 10; ++i) {
        bvector_append(vector, bnode_decimal(i));
        val += 1.131;
    }

    bvector_print_normal(vector);

    printf("\n");

    bnode_set_decimal(bvector_fetch(vector, 1), 141.121);
    bnode_set_decimal(bvector_fetch(vector, 3), 323.383);
    bnode_set_decimal(bvector_fetch(vector, 4), 414.474);

    bvector_print_normal(vector);
    printf("\n");

    printf("fetch index[%d] value: %Lf from vector.\n", 1, bnode_to_decimal(bvector_fetch(vector, 1)));
    printf("fetch index[%d] value: %Lf from vector.\n", 4, bnode_to_decimal(bvector_fetch(vector, 4)));

    bvector_destroy(vector);
}

void string_test()
{
    BridgeVector *vector = bvector_create(B_String);

    if (!vector) {
        return;
    }

    bvector_append(vector, bnode_string("string1"));
    bvector_append(vector, bnode_string("string2"));
    bvector_append(vector, bnode_string("string3"));
    bvector_append(vector, bnode_string("string4"));
    bvector_append(vector, bnode_string("string5"));
    bvector_append(vector, bnode_string("string6"));

    bvector_print_normal(vector);
    printf("\n");

    bnode_set_string(bvector_fetch(vector, 1), "str111");
    bnode_set_string(bvector_fetch(vector, 3), "str333");
    bnode_set_string(bvector_fetch(vector, 4), "str444");

    bvector_print_normal(vector);
    printf("\n");

    printf("fetch index[%d] value: %s from vector.\n", 1, bnode_to_string(bvector_fetch(vector, 1)));
    printf("fetch index[%d] value: %s from vector.\n", 4, bnode_to_string(bvector_fetch(vector, 4)));

    bvector_destroy(vector);
}

void object_test()
{
    BridgeVector *vector = bvector_create(B_Object);

    if (!vector) {
        return;
    }

    int i, size = sizeof(Student);
    Student student;

    for (i = 0; i < 10; ++i) {
        student.no = i + 1;
        student.age = 18 + i * 2;
        snprintf(student.name, 20, "name%d", i);
        bvector_append(vector, bnode_object2(&student, size));
    }

    bvector_print_callback(vector, student_print);
    printf("\n");

    student.no = 100;
    student.age = 512;
    snprintf(student.name, 20, "name%d", 100);
    bvector_set_object(vector, 1, &student, size);
    bvector_set_object(vector, 3, &student, size);
    bvector_set_object(vector, 4, &student, size);

    bvector_print_callback(vector, student_print);
    printf("\n");

    student_print(bnode_to_object(bvector_fetch(vector, 1)));
    student_print(bnode_to_object(bvector_fetch(vector, 4)));
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
    object_test();
    printf("---------------------------\n");
    return 0;
}