#ifndef CTK_LIST_H
#define CTK_LIST_H

#include <stddef.h>

typedef struct {
    void **data;
    size_t size;
    size_t cap;
} ctk_list_t;

void ctk_list_init(ctk_list_t *list, size_t initcap);

void ctk_list_destruct(ctk_list_t *list);

void ctk_list_add(ctk_list_t *list, void *entry);

void **ctk_list_move_raw(ctk_list_t *list);

#endif
