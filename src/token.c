#include "ctk/token.h"

static char **ctk_token_names = NULL;

void ctk_token_init(ctk_token_t *tok, int kind, ctk_textsrc_t *src,
                    ctk_textpos_t *pos, ctk_strspan_t *lexeme) {
    tok->kind = kind;
    tok->src = src;
    tok->pos = *pos;
    tok->lexeme = *lexeme;
}

void ctk_token_write(ctk_token_t *tok, FILE *file) {
    ctk_token_write_with_names(tok, ctk_token_names, file);
}

void ctk_token_write_with_names(ctk_token_t *tok, char *names[], FILE *file) {
    fprintf(file, "%s:%d:%d: ", 
            tok->src->name, tok->pos.line, tok->pos.col);
    
    if (names == NULL) {
        fprintf(file, "<%d> ", tok->kind);
    } else {
        fprintf(file, "<%s> ", names[tok->kind]);
    }

    ctk_strspan_write_repr(&tok->lexeme, file);
}

void ctk_tokenkind_set_name_table(char *names[]) {
    ctk_token_names = names;
}
