#include "ctk/map.h"
#include <string.h>
#include <assert.h>

static bool ctk_str_is_equal(void *p1, void *p2) {
    return strcmp(p1, p2) == 0;
}

static ctk_hash_t ctk_str_hash(void *p) {
    (void)p;
    return 0;
}

static bool ctk_identity_is_equal(void *p1, void *p2) {
    return p1 == p2;
}

static ctk_hash_t ctk_identity_hash(void *p) {
    (void)p;
    return 0;
}

ctk_map_definition_t const ctk_strmap_def = {
    .is_equal = &ctk_str_is_equal,
    .hash = &ctk_str_hash,
};

ctk_map_definition_t const ctk_identitymap_def = {
    .is_equal = &ctk_identity_is_equal,
    .hash = &ctk_identity_hash,
};

static inline ctk_map_entry_t *ctk_linmap_get_entry(ctk_linmap_t *map, 
                                                    size_t i) {
    uintptr_t p = (uintptr_t)map->entries.data + i * sizeof(ctk_map_entry_t);
    return (ctk_map_entry_t *)p;
}

static inline void ctk_linmap_remove_last(ctk_linmap_t *map) {
    map->entries.size -= sizeof(ctk_map_entry_t);
}

static inline ctk_map_entry_t *ctk_linmap_lookup_entry(ctk_linmap_t *map, 
                                                       void *key) {
    size_t size = ctk_linmap_size(map);
    for (size_t i = 0; i < size; i++) {
        ctk_map_entry_t *entry = ctk_linmap_get_entry(map, i);

        if (map->def->is_equal(key, entry->key)) {
            return entry;
        }
    }

    return NULL;
}

void ctk_linmap_init(ctk_linmap_t *map, ctk_map_definition_t const *def) {
    map->def = def;
    ctk_dynarr_init(&map->entries, 4 * sizeof(ctk_map_entry_t));
}

void ctk_linmap_destruct(ctk_linmap_t *map) {
    ctk_dynarr_destruct(&map->entries);
}

void ctk_linmap_pop(ctk_linmap_t *map, ctk_map_entry_t *dst) {
    size_t size = ctk_linmap_size(map);
    assert(size > 0);

    ctk_map_entry_t *entry = ctk_linmap_get_entry(map, size - 1);
    *dst = *entry;
    ctk_linmap_remove_last(map);
}

size_t ctk_linmap_size(ctk_linmap_t *map) {
    return map->entries.size / sizeof(ctk_map_entry_t);
}

void *ctk_linmap_insert(ctk_linmap_t *map, void *key, void *val) {
    ctk_map_entry_t *entry = ctk_linmap_lookup_entry(map, key);
    if (entry != NULL) {
        return entry->val;
    }

    entry = ctk_dynarr_add(&map->entries, sizeof(ctk_map_entry_t));

    entry->key = key;
    entry->val = val;

    return NULL;
}

void *ctk_linmap_lookup(ctk_linmap_t *map, void *key) {
    ctk_map_entry_t *entry = ctk_linmap_lookup_entry(map, key);
    if (entry == NULL) {
        return NULL;
    }

    return entry->val;
}

void *ctk_linmap_delete(ctk_linmap_t *map, void *key) {
    ctk_map_entry_t *entry = ctk_linmap_lookup_entry(map, key);
    if (entry == NULL) {
        return NULL;
    }

    void *val = entry->val;
    size_t size = ctk_linmap_size(map);
    ctk_map_entry_t *last = ctk_linmap_get_entry(map, size - 1);

    if (entry != last) {
        *entry = *last;
    }

    ctk_linmap_remove_last(map);
    return val;
}

void ctk_linmap_iter_init(ctk_linmap_iter_t *iter, ctk_linmap_t *map);

void ctk_linmap_iter_next(ctk_linmap_iter_t *iter);

bool ctk_linmap_iter_at_end(ctk_linmap_iter_t *iter);
