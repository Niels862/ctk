#include "ctk/dynamic-array.h"
#include "ctk/allocator.h"
#include <stdio.h>

void ctk_dynarr_init(ctk_dynarr_t *arr, size_t initcap) {
    arr->cap = initcap;
    arr->size = 0;
    arr->data = ctk_xmalloc(arr->cap);
}

void ctk_dynarr_destruct(ctk_dynarr_t *arr) {
    ctk_free(&arr->data);
}

static void ctk_dynarr_realloc(ctk_dynarr_t *arr) {
    if (arr->size <= arr->cap) {
        return;
    }

    while (arr->size > arr->cap) {
        arr->cap *= 2;
    }

    ctk_xrealloc(&arr->data, arr->cap);
}

void *ctk_dynarr_add(ctk_dynarr_t *arr, size_t size) {
    size_t i = arr->size;
    arr->size += size;
    
    ctk_dynarr_realloc(arr);

    return (void *)((uintptr_t)arr->data + i);
}

void *ctk_dynarr_move(ctk_dynarr_t *arr) {
    void *data = arr->data;
    arr->data = NULL;
    return data;
}
