#include "ctk/parser.h"
#include <stddef.h>
#include <assert.h>

static ctk_token_t ctk_invalid_token = {
    .kind = 0,
};

void ctk_parser_init(ctk_parser_t *parser, ctk_span_t *span) {
    parser->curr = span->start;
    parser->end = span->end;
}

bool ctk_parser_at_end(ctk_parser_t *parser) {
    assert(parser->curr <= parser->end);
    return parser->curr == parser->end;
}

void ctk_parser_advance(ctk_parser_t *parser) {
    if (!ctk_parser_at_end(parser)) {
        parser->curr++;
    }
}

ctk_token_t *ctk_parser_accept(ctk_parser_t *parser, int kind) {
    ctk_token_t *curr = ctk_parser_curr(parser);

    if (curr->kind == kind) {
        ctk_parser_advance(parser);
        return curr;
    }

    return NULL;
}

ctk_token_t *ctk_parser_expect(ctk_parser_t *parser, int kind) {
    ctk_token_t *curr = ctk_parser_curr(parser);

    if (curr->kind == kind) {
        ctk_parser_advance(parser);
        return curr;
    }

    /* FIXME: needs to write to a modular, user defined function. 
       Needs to handle the end token with a different name and cannot 
       use get_name. */
    fprintf(stderr, "expected '%s', got '%s'\n", 
            ctk_tokenkind_get_name(kind), ctk_tokenkind_get_name(curr->kind));
    return NULL;
}

ctk_token_t *ctk_parser_curr(ctk_parser_t *parser) {
    if (ctk_parser_at_end(parser)) {
        return &ctk_invalid_token;
    }
    return parser->curr;
}

ctk_token_t *ctk_parser_peek(ctk_parser_t *parser, int n) {
    ptrdiff_t diff = parser->end - parser->curr;
    if (diff < n) {
        return parser->curr + n;
    }
    return &ctk_invalid_token;
}
