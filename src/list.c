#include "ctk/list.h"
#include "ctk/allocator.h"
#include <assert.h>

void ctk_list_init(ctk_list_t *list, size_t initcap) {
    ctk_dynarr_init(list, initcap * sizeof(void *));
}

void ctk_list_destruct(ctk_list_t *list) {
    ctk_dynarr_destruct(list);
}

void ctk_list_add(ctk_list_t *list, void *entry) {
    void **p = ctk_dynarr_add(list, sizeof(void *));
    assert((uintptr_t)p % sizeof(void *) == 0);
    *p = entry;
}

size_t ctk_list_size(ctk_list_t *list) {
    return list->size / sizeof(void *);
}

void **ctk_list_move(ctk_list_t *list) {
    ctk_list_add(list, NULL);
    return ctk_dynarr_move(list);
}
