#include "ctk/list.h"
#include "ctk/allocator.h"

void ctk_list_init(ctk_list_t *list, size_t initcap) {
    list->cap = initcap;
    list->data = ctk_xmalloc(list->cap * sizeof(void *));
    list->size = 0;
}

void ctk_list_destruct(ctk_list_t *list) {
    ctk_free(&list->data);
}

void ctk_list_add(ctk_list_t *list, void *entry) {
    if (list->size + 1 > list->cap) {
        list->cap *= 2;
        ctk_xrealloc(&list->data, list->cap * sizeof(void *));
    }

    list->data[list->size] = entry;
    list->size++;
}

void **ctk_list_move_raw(ctk_list_t *list) {
    ctk_list_add(list, NULL);

    void **data = list->data;
    list->data = NULL;
    
    return data;
}
