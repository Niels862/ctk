#include "ctk/rtti.h"
#include "ctk/list.h"
#include "ctk/allocator.h"
#include <stdio.h>
#include <stdint.h>

typedef struct {
    ctk_rtti_t *meta;
} node_base_t;

typedef struct {
    node_base_t base;
    void *type;
} node_expr_t;

typedef struct {
    node_base_t base;
} node_stmt_t;

typedef struct {
    node_expr_t expr;
    int64_t lit;
} node_intlit_t;

typedef struct {
    node_expr_t expr;
    void **entries;
} node_list_t;

static ctk_rtti_t node_base_rtti = {
    .super = &ctk_rtti_base,
    .name = "node-base",
};

static ctk_rtti_t node_expr_rtti = {
    .super = &node_base_rtti,
    .name = "node-expr",
    .attrs = CTK_RTTI_ATTR_LIST(
        CTK_RTTI_ATTR(node_expr_t, type, CTK_TYPE_INVALID)
    ),
};

static ctk_rtti_t node_stmt_rtti = {
    .super = &node_base_rtti,
    .name = "node-stmt",
};

static ctk_rtti_t node_intlit_rtti = {
    .super = &node_expr_rtti,
    .name = "node-intlit",
    .attrs = CTK_RTTI_ATTR_LIST(
        CTK_RTTI_ATTR(node_intlit_t, lit, CTK_TYPE_I64)
    )
};

static ctk_rtti_t node_list_rtti = {
    .super = &node_expr_rtti,
    .name = "node-list",
    .attrs = CTK_RTTI_ATTR_LIST(
        CTK_RTTI_ATTR(node_list_t, entries, CTK_TYPE_RTTI_LIST)
    )
};

/* Would be in file.h */
CTK_RTTI_DECL(node, base)
CTK_RTTI_DECL(node, expr)
CTK_RTTI_DECL(node, stmt)
CTK_RTTI_DECL(node, intlit)
CTK_RTTI_DECL(node, list)

static void base_init(node_base_t *base, ctk_rtti_t *meta) {
    base->meta = meta;
}

static void expr_init(node_expr_t *expr, ctk_rtti_t *meta) {
    base_init(&expr->base, meta);
    expr->type = NULL;
}

static node_intlit_t *intlit_new(int64_t lit) {
    node_intlit_t *node = node_intlit_xalloc();

    expr_init(&node->expr, &node_intlit_rtti);
    node->lit = lit;

    return node;
}

static node_list_t *list_new(ctk_list_t *entries) {
    node_list_t *node = node_list_xalloc();

    expr_init(&node->expr, &node_list_rtti);
    node->entries = ctk_list_move_raw(entries);

    return node;
}

/* Would be in file.c */
CTK_RTTI_DEFN(node, base)
CTK_RTTI_DEFN(node, expr)
CTK_RTTI_DEFN(node, stmt)
CTK_RTTI_DEFN(node, intlit)
CTK_RTTI_DEFN(node, list)

int main(void) {
    node_intlit_t *intlit = intlit_new(42);

    bool isexpr = node_expr_instanceof(intlit);
    bool isstmt = node_stmt_instanceof(intlit);
    bool isbase = node_base_instanceof(intlit);
    
    node_expr_t *expr = node_expr_dyncast(intlit);
    node_stmt_t *stmt = node_stmt_dyncast(intlit);
    node_base_t *base = node_base_dyncast(intlit);

    fprintf(stderr, "%d %d %d\n", isexpr, isstmt, isbase);
    fprintf(stderr, "%p %p %p\n", (void *)expr, (void *)stmt, (void *)base);

    ctk_rtti_delete(intlit);

    ctk_list_t entries;
    ctk_list_init(&entries, 2);

    for (size_t i = 0; i < 64; i++) {
        node_intlit_t *intlit = intlit_new(1LL << i);
        ctk_list_add(&entries, intlit);
    }

    node_list_t *list = list_new(&entries);

    ctk_rtti_write(list, 0, stderr);
    fprintf(stderr, "\n");

    ctk_rtti_delete(list);

    return 0;
}
