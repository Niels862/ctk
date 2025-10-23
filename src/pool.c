#include "ctk/pool.h"
#include "ctk/allocator.h"
#include <assert.h>

void ctk_pool_init(ctk_pool_t *pool) {
    pool->block = NULL;
    pool->blocksize = 4096 - sizeof(ctk_poolblock_t);
}

void ctk_pool_destruct(ctk_pool_t *pool) {
    ctk_poolblock_t *block = pool->block;

    while (block != NULL) {
        ctk_poolblock_t *next = block->next;
        ctk_xfree(&block);
        block = next;
    }
}

static ctk_poolblock_t *ctk_pool_alloc_block(ctk_pool_t *pool, size_t size) {
    ctk_poolblock_t *block = ctk_xmalloc(size + sizeof(ctk_poolblock_t));

    block->next = pool->block;
    pool->block = block;

    return block;
}

static void *ctk_pool_fresh_block_alloc(ctk_pool_t *pool, size_t size) {
    size_t blocksize;
    if (size < pool->blocksize) {
        blocksize = pool->blocksize;
    } else {
        blocksize = size;
    }

    ctk_poolblock_t *block = ctk_pool_alloc_block(pool, blocksize);
    block->used = size;

    return block->payload;
}

void *ctk_pool_alloc_aligned(ctk_pool_t *pool, size_t size, size_t align) {
    assert(align == 1 || align == 2 || align == 4 || align == 8);

    if (pool->block == NULL) {
        goto fresh;
    }

    if (pool->blocksize < size) {
        goto fresh;
    }

    size_t aligner = align - pool->block->used % align;
    if (aligner == align) {
        aligner = 0;
    }

    size_t at = pool->block->used + aligner;
    if (at + size > pool->blocksize) {
        goto fresh;
    }

    return pool->block->payload + at;

fresh:
    return ctk_pool_fresh_block_alloc(pool, size);
}

void *ctk_pool_alloc(ctk_pool_t *pool, size_t size) {
    return ctk_pool_alloc_aligned(pool, size, sizeof(void *));
}
