#ifndef CTK_TOKEN_H
#define CTK_TOKEN_H

#include "ctk/text-position.h"
#include "ctk/text-source.h"
#include "ctk/string-span.h"
#include <stdio.h>

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

void ctk_tokenkind_set_name_table(char **names);

char *ctk_tokenkind_get_name(int kind);

#endif
