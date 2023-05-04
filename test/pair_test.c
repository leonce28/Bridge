#include "pair.h"

void string_integer_test()
{
    BridgePair *pair = bpair_make_string_integer("string key", 32);
    printf("%s : %d\n", bpair_first_string(pair), bpair_second_integer(pair));
}

int main(int argc, char *argv[])
{
    // integer_integer_test();
    // integer_decimal_test();
    // integer_string_test();
    // integer_pointer_test();

    string_integer_test();
    // string_decimal_test();
    // string_string_test();
    // string_pointer_test();

    // decimal_integer_test();
    // decimal_decimal_test();
    // decimal_string_test();
    // decimal_pointer_test();

    // pointer_integer_test();
    // pointer_decimal_test();
    // pointer_string_test();
    // pointer_pointer_test();

    return 0;
}