#ifndef CTK_POOL_H
#define CTK_POOL_H

#include <stddef.h>
#include <stdint.h>

typedef struct ctk_poolblock_t ctk_poolblock_t;

struct ctk_poolblock_t {
    ctk_poolblock_t *next;
    size_t used;
    uint8_t payload[];
};

typedef struct {
    ctk_poolblock_t *block;
    size_t blocksize;
} ctk_pool_t;

void ctk_pool_init(ctk_pool_t *pool);

void ctk_pool_destruct(ctk_pool_t *pool);

void *ctk_pool_alloc_aligned(ctk_pool_t *pool, size_t size, size_t align);

void *ctk_pool_alloc(ctk_pool_t *pool, size_t size);

#endif
