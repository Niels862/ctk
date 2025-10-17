#ifndef CTK_PARSER_H
#define CTK_PARSER_H

#include "ctk/token.h"
#include "ctk/span.h"
#include <stdbool.h>

typedef struct {
    ctk_token_t *curr;
    ctk_token_t *end;
} ctk_parser_t;

void ctk_parser_init(ctk_parser_t *parser, ctk_span_t *span);

bool ctk_parser_at_end(ctk_parser_t *parser);

void ctk_parser_advance(ctk_parser_t *parser);

ctk_token_t *ctk_parser_accept(ctk_parser_t *parser, int kind);

ctk_token_t *ctk_parser_expect(ctk_parser_t *parser, int kind);

ctk_token_t *ctk_parser_curr(ctk_parser_t *parser);

ctk_token_t *ctk_parser_peek(ctk_parser_t *parser, int n);

#endif
