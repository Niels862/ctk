#ifndef CTK_DYNAMIC_ARRAY_H
#define CTK_DYNAMIC_ARRAY_H

#include <stdint.h>
#include <stddef.h>

typedef struct {
    void *data;
    size_t size;
    size_t cap;
} ctk_dynarr_t;

void ctk_dynarr_init(ctk_dynarr_t *arr, size_t initcap);

void ctk_dynarr_destruct(ctk_dynarr_t *arr);

void *ctk_dynarr_add(ctk_dynarr_t *arr, size_t size);

void *ctk_dynarr_move(ctk_dynarr_t *arr);

#endif
