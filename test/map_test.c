#include <stdio.h>
#include "map.h"
#include "test.h"

int main() 
{
    size_t i;
    BridgePair *pair = NULL;
    BridgeMap *map = bmap_create();
    if (!map) {
        return 0;
    }

    bmap_udf_free(map, student_free);
    bmap_udf_hash(map, student_hash);
    bmap_udf_tostr(map, student_tostr);
    bmap_udf_compare(map, student_compare);

    pair = bpair_make(bnode_string("apple"), bnode_integer(11));
    bmap_put_pair(map, pair);

    pair = bpair_make(bnode_string("banana"), bnode_integer(22));
    bmap_put_pair(map, pair);

    pair = bpair_make(bnode_string("cherry"), bnode_integer(33));
    bmap_put_pair(map, pair);

    pair = bpair_make(bnode_string("durian"), bnode_integer(44));
    bmap_put_pair(map, pair);

    pair = bpair_make(bnode_string("elderberry"), bnode_integer(55));
    bmap_put_pair(map, pair);

    bmap_print(map);
    printf("\n");

    if ((pair = bmap_find_pair(map, bnode_string("cherry"))) != nullptr) {
        printf("find: %s : %lld\n", 
            bnode_to_string(bpair_first(pair)), bnode_to_integer(bpair_second(pair)));
        
        bnode_set_integer(bpair_second(pair), 996);
    }

    bmap_erase_pair(map, bnode_string("banana"));
    bmap_erase_pair(map, bnode_string("durian"));

    bmap_print(map);
    printf("\n");

    bmap_destroy(map);
    
    return 0;
}