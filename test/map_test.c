#include <stdio.h>
#include "map.h"
#include "test.h"

void string_integer_test()
{
    size_t i;
    BridgePair *pair = NULL;
    BridgeMap *map = bmap_create(B_String, B_Integer);
    if (!map) {
        return;
    }

    const char *keys[] = { "apple", "banana", "cherry", "durian", "elderberry" };
    int values[] = { 1, 2, 3, 4, 5 };

    for (i = 0; i < sizeof(keys) / sizeof(keys[0]); i++) {
        pair = bpair_make(bnode_create_sval(keys[i]), bnode_create_ival(values[i]));
        bmap_put_pair(map, pair);
    }

    bmap_print_normal(map);
    printf("\n");

    pair = bmap_find_pair_sval(map, "banana");
    printf("%s : %lld\n", bpair_first_sval(pair), bpair_second_ival(pair));

    bmap_erase_sval(map, "banana");
    bmap_erase_sval(map, "durian");

    bmap_print_normal(map);
    printf("\n");

    bvector_destroy(map);
}

void decimal_test()
{

}

void string_test()
{
   
}

void pointer_test()
{
 
}

int main() 
{
    printf("---------------------------\n");
    string_integer_test();
    printf("---------------------------\n");
    decimal_test();
    printf("---------------------------\n");
    string_test();
    printf("---------------------------\n");
    pointer_test();
    printf("---------------------------\n");
    return 0;
}