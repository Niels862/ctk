#include "ctk/parser.h"
#include <stddef.h>
#include <assert.h>

static ctk_token_t ctk_invalid_token = {
    .kind = 0,
};

void ctk_parser_init(ctk_parser_t *parser, ctk_span_t *span, 
                     ctk_parser_expect_error_t expect_error) {
    parser->curr = span->start;
    parser->end = span->end;
    parser->expect_error = expect_error;
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

ctk_token_t *ctk_parser_expect(ctk_parser_t *parser, 
                               int kind, char const *msg) {
    ctk_token_t *curr = ctk_parser_curr(parser);

    if (curr->kind == kind) {
        ctk_parser_advance(parser);
        return curr;
    }

    parser->expect_error(curr, kind, msg);
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
