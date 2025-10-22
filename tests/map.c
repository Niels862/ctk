#include "ctk/map.h"
#include <stdio.h>
#include <assert.h>

typedef struct {
    void *p1;
    void *p2;
} pair_t;

int main() {
    pair_t pairs[] = {
        { "a", "123" },
        { "b", "!" },
        { "", "<empty key>" },
        { "123", "" }
    };

    ctk_linmap_t map;
    ctk_linmap_init(&map, &ctk_strmap_def);

    ctk_map_entry_t *prev;
    for (size_t i = 0; i < sizeof(pairs) / sizeof(*pairs); i++) {
        prev = ctk_linmap_insert(&map, pairs[i].p1, pairs[i].p2);
        assert(prev == NULL);
    }

    for (size_t i = 0; i < sizeof(pairs) / sizeof(*pairs); i++) {
        void *val = ctk_linmap_lookup(&map, pairs[i].p1);
        assert(val != NULL);
        printf("[%s] = %s (%s)\n", 
               (char *)pairs[i].p1, (char *)val, (char *)pairs[i].p2);
    }

    ctk_linmap_destruct(&map);

    return 0;
}
