#include "ctk/token-list.h"
#include "ctk/allocator.h"
#include <assert.h>

#define CTK_TOKENLIST_INIT_CAP 16

void ctk_tokenlist_init(ctk_tokenlist_t *toks) {
    toks->cap = CTK_TOKENLIST_INIT_CAP;
    toks->size = 0;
    toks->data = ctk_xmalloc(toks->cap * sizeof(ctk_token_t));
    toks->locked = false;
}

void ctk_tokenlist_destruct(ctk_tokenlist_t *toks) {
    ctk_free(&toks->data);
}

void ctk_tokenlist_add(ctk_tokenlist_t *toks, ctk_token_t *tok) {
    if (toks->size + 1 >= toks->cap) {
        toks->cap *= 2;
        ctk_xrealloc(&toks->data, toks->cap * sizeof(ctk_token_t));
    }

    toks->data[toks->size] = *tok;
    toks->size++;
}

void ctk_tokenlist_finalize(ctk_tokenlist_t *toks) {
    assert(toks->size >= 2);
    assert(toks->data[0].kind == CTK_TOKEN_STARTSOURCE);
    assert(toks->data[toks->size - 1].kind == CTK_TOKEN_ENDSOURCE);

    for (size_t i = 1; i < toks->size - 1; i++) {
        (void)i;
        assert(toks->data[i].kind > 0 && toks->data[i].kind < 0x100);
    }

    toks->locked = true;
}

void ctk_tokenlist_to_span(ctk_tokenlist_t *toks, ctk_span_t *span) {
    assert(toks->locked);

    span->start = &toks->data[0];
    span->end   = &toks->data[toks->size];
}
