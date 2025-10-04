#ifndef CTK_RTTI_H
#define CTK_RTTI_H

#include "ctk/string-utils.h"
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>

typedef enum {
    CTK_TYPE_INVALID,
    CTK_TYPE_RTTI,

    CTK_TYPE_I64,
    CTK_TYPE_BOOL,
    CTK_TYPE_ZSTR,
} ctk_rtti_type_t;

typedef struct {
    ctk_zstr_t name;
    ctk_rtti_type_t type;
    size_t offset;
} ctk_rtti_attr_t;

#define CTK_RTTI_ATTR(s, a, t) { #a, t, offsetof(s, a) }

typedef struct {
    ctk_rtti_attr_t *list;
    size_t n;
} ctk_rtti_attrlist_t;

#define CTK_RTTI_ATTR_LIST(as) { as, sizeof(as) / sizeof(*as) }

typedef struct ctk_rtti_t ctk_rtti_t;

struct ctk_rtti_t {
    ctk_rtti_t *super;
    ctk_zstr_t name;
    ctk_rtti_attrlist_t attrs;
};

#define CTK_RTTI_META(p) (*(ctk_rtti_t **)(p))

extern ctk_rtti_t ctk_rtti_base;

void ctk_rtti_delete(void *obj);

bool ctk_rtti_instanceof(void *obj, ctk_rtti_t *meta);

void *ctk_rtti_dyncast(void *obj, ctk_rtti_t *meta);

void ctk_rtti_write(void *obj, size_t depth, FILE *file);

#define CTK_RTTI_TYPENAME(pre, t) pre##_##t##_t

#define CTK_RTTI_METANAME(pre, t) pre##_##t##_rtti

#define CTK_RTTI_DECL(pre, t) \
    bool pre##_##t##_instanceof(void *obj); \
    CTK_RTTI_TYPENAME(pre, t) *pre##_##t##_dyncast(void *obj);


#define CTK_RTTI_DEFN(pre, t) \
    bool pre##_##t##_instanceof(void *obj) \
        { return ctk_rtti_instanceof(obj, &CTK_RTTI_METANAME(pre, t)); } \
    CTK_RTTI_TYPENAME(pre, t) *pre##_##t##_dyncast(void *obj) \
        { return ctk_rtti_dyncast(obj, &CTK_RTTI_METANAME(pre, t)); }

#endif
