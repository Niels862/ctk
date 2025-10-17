#ifndef CTK_RTTI_H
#define CTK_RTTI_H

#include "ctk/allocator.h"
#include "ctk/string-utils.h"
#include "ctk/token.h"
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>

#ifndef CTK_RTTI_MAX_ATTRS
#define CTK_RTTI_MAX_ATTRS 8
#endif

typedef enum {
    CTK_TYPE_INVALID,

    CTK_TYPE_RTTI,
    CTK_TYPE_RTTI_LIST,

    CTK_TYPE_TOKEN,

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

#define CTK_RTTI_ATTR_LIST(...) { __VA_ARGS__, { 0 } }

typedef struct ctk_rtti_t ctk_rtti_t;

struct ctk_rtti_t {
    ctk_rtti_t *super;
    ctk_zstr_t name;
    ctk_rtti_attr_t attrs[CTK_RTTI_MAX_ATTRS];
};

#define CTK_RTTI_META(p) (*(ctk_rtti_t **)(p))

extern ctk_rtti_t ctk_rtti_base;

void ctk_rtti_delete(void *obj);

void ctk_rtti_list_delete(void **list);

bool ctk_rtti_instanceof(void *obj, ctk_rtti_t *meta);

void *ctk_rtti_dyncast(void *obj, ctk_rtti_t *meta);

void ctk_rtti_write(void *obj, size_t depth, FILE *file);

#define CTK_RTTI_TYPENAME(pre, t) pre##_##t##_t

#define CTK_RTTI_METANAME(pre, t) pre##_##t##_rtti

#define CTK_RTTI_DECL(pre, t) \
    bool pre##_##t##_instanceof(void *obj); \
    CTK_RTTI_TYPENAME(pre, t) *pre##_##t##_dyncast(void *obj); \
    CTK_RTTI_TYPENAME(pre, t) *pre##_##t##_xalloc(void);

#define CTK_RTTI_DEFN(pre, t) \
    bool pre##_##t##_instanceof(void *obj) \
        { return ctk_rtti_instanceof(obj, &CTK_RTTI_METANAME(pre, t)); } \
    CTK_RTTI_TYPENAME(pre, t) *pre##_##t##_dyncast(void *obj) \
        { return ctk_rtti_dyncast(obj, &CTK_RTTI_METANAME(pre, t)); } \
    CTK_RTTI_TYPENAME(pre, t) *pre##_##t##_xalloc(void) \
        { return ctk_xmalloc(sizeof(CTK_RTTI_TYPENAME(pre, t))); }

#endif
