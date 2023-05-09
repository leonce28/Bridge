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
        pair = bpair_make(bnode_string(keys[i]), bnode_integer(values[i]));
        bmap_put_pair(map, pair);
    }

    bmap_print_normal(map);
    printf("\n");

    pair = bmap_find_pair(map, bnode_string("banana"));
    printf("%s : %lld\n", bnode_to_string(bpair_first(pair)), bnode_to_integer(bpair_second(pair)));

    bmap_erase_pair(map, bnode_string("banana"));
    bmap_erase_pair(map, bnode_string("durian"));

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

void object_test()
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
    object_test();
    printf("---------------------------\n");
    return 0;
}