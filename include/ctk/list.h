#ifndef CTK_LIST_H
#define CTK_LIST_H

#include "ctk/dynamic-array.h"
#include <stddef.h>

typedef ctk_dynarr_t ctk_list_t;

void ctk_list_init(ctk_list_t *list, size_t initcap);

void ctk_list_destruct(ctk_list_t *list);

void ctk_list_add(ctk_list_t *list, void *entry);

size_t ctk_list_size(ctk_list_t *list);

void **ctk_list_move(ctk_list_t *list);

#endif
