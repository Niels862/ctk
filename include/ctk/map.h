#ifndef CTK_MAP_H
#define CTK_MAP_H

#include "ctk/dynamic-array.h"
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint32_t ctk_hash_t;

typedef bool(*ctk_is_equal_func_t)(void *p1, void *p2);
typedef ctk_hash_t(*ctk_hash_func_t)(void *p);

typedef struct {
    ctk_is_equal_func_t is_equal;
    ctk_hash_func_t hash;
} ctk_map_definition_t;

extern ctk_map_definition_t const ctk_strmap_def;
extern ctk_map_definition_t const ctk_identitymap_def;

typedef struct {
    void *key;
    void *val;
} ctk_map_entry_t;

typedef struct {
    ctk_map_definition_t const *def;
    ctk_dynarr_t entries;
} ctk_linmap_t;

typedef struct {
    ctk_linmap_t *map;
    size_t i;
    ctk_map_entry_t entry;
} ctk_linmap_iter_t;

void ctk_linmap_init(ctk_linmap_t *map, ctk_map_definition_t const *def);

void ctk_linmap_destruct(ctk_linmap_t *map);

/* Can be used for destructing values before destructing the map. */
void ctk_linmap_pop(ctk_linmap_t *map, ctk_map_entry_t *dst);

size_t ctk_linmap_size(ctk_linmap_t *map);

void *ctk_linmap_insert(ctk_linmap_t *map, void *key, void *val);

void *ctk_linmap_lookup(ctk_linmap_t *map, void *key);

void *ctk_linmap_delete(ctk_linmap_t *map, void *key);

void ctk_linmap_iter_init(ctk_linmap_iter_t *iter, ctk_linmap_t *map);

void ctk_linmap_iter_next(ctk_linmap_iter_t *iter);

bool ctk_linmap_iter_at_end(ctk_linmap_iter_t *iter);

#endif 
