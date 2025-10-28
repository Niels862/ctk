#ifndef CTK_TOKEN_LIST_H
#define CTK_TOKEN_LIST_H

#include "token.h"
#include "span.h"
#include <stdbool.h>

typedef enum {
    CTK_TOKEN_NONE,
    CTK_TOKEN_STARTSOURCE,
    CTK_TOKEN_ENDSOURCE,
} ctk_builtin_tokenkind_t;

#define CTK_TOKEN_USER_START    (CTK_TOKEN_ENDSOURCE + 1)

typedef struct {
    size_t size;
    size_t cap;
    ctk_token_t *data;
    bool locked;
} ctk_tokenlist_t;

void ctk_tokenlist_init(ctk_tokenlist_t *toks);

void ctk_tokenlist_destruct(ctk_tokenlist_t *toks);

void ctk_tokenlist_add(ctk_tokenlist_t *toks, ctk_token_t *tok);

void ctk_tokenlist_finalize(ctk_tokenlist_t *toks);

void ctk_tokenlist_to_span(ctk_tokenlist_t *toks, ctk_span_t *span);

#endif
