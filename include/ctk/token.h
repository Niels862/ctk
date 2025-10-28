#ifndef CTK_TOKEN_H
#define CTK_TOKEN_H

#include "ctk/text-position.h"
#include "ctk/text-source.h"
#include "ctk/string-span.h"
#include "ctk/span.h"
#include <stdio.h>

typedef enum {
    CTK_TOKEN_NONE              = 0,
    CTK_TOKEN_STARTSOURCE       = 0x100 | 0,
    CTK_TOKEN_ENDSOURCE         = 0x100 | 1,
} ctk_builtin_tokenkind_t;

typedef struct {
    int kind;
    ctk_textsrc_t *src;
    ctk_textpos_t pos;
    ctk_strspan_t lexeme;
} ctk_token_t;

void ctk_token_init(ctk_token_t *tok, int kind, ctk_textsrc_t *src,
                    ctk_textpos_t *pos, ctk_strspan_t *lexeme);

void ctk_token_write(ctk_token_t *tok, FILE *file);

void ctk_token_write_with_names(ctk_token_t *tok, char *names[], FILE *file);

void ctk_token_short_write(ctk_token_t *tok, FILE *file);

void ctk_line_context_write(ctk_span_t *line, ctk_span_t *highlight, 
                            FILE *file);

void ctk_tokenkind_set_name_table(char **names);

char *ctk_tokenkind_get_name(int kind);

#endif
