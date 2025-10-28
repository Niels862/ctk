#include "ctk/token.h"
#include "ctk/string-utils.h"

static char **ctk_token_names = NULL;

void ctk_token_init(ctk_token_t *tok, int kind, ctk_textsrc_t *src,
                    ctk_textpos_t *pos, ctk_strspan_t *lexeme) {
    tok->kind = kind;
    tok->src = src;
    tok->pos = *pos;
    tok->lexeme = *lexeme;
}

void ctk_token_write(ctk_token_t *tok, FILE *file) {
    fprintf(file, "%s:%d:%d: ", 
            tok->src->name, tok->pos.line, tok->pos.col);
    fprintf(file, "<%s> ", ctk_tokenkind_get_name(tok->kind));
    ctk_strspan_write_repr(&tok->lexeme, file);
}

void ctk_token_short_write(ctk_token_t *tok, FILE *file) {
    fprintf(file, "%s:%d:%d: ", 
            tok->src->name, tok->pos.line, tok->pos.col);
    ctk_strspan_write_repr(&tok->lexeme, file);
}

ctk_token_t *ctk_line_find_start(ctk_token_t *tok) {
    int line = tok->pos.line;

    while (tok->kind != CTK_TOKEN_STARTSOURCE && tok->pos.line == line) {
        tok--;
    }

    return tok;
}

ctk_token_t *ctk_line_find_end(ctk_token_t *tok) {
    int line = tok->pos.line;

    while (tok->kind != CTK_TOKEN_ENDSOURCE && tok->pos.line == line) {
        tok++;
    }

    return tok;
}

void ctk_line_context_write(ctk_span_t *line, ctk_span_t *highlight, 
                            FILE *file) {
    (void)highlight;

    for (ctk_token_t *tok = line->start; tok != line->end; tok++) {
        ctk_str_write(tok->lexeme.start, tok->lexeme.end, file);
    }
}

void ctk_tokenkind_set_name_table(char *names[]) {
    ctk_token_names = names;
}

char *ctk_tokenkind_get_name(int kind) {
    if (kind & 0x100) {
        switch (kind & 0xFF) {
            case CTK_TOKEN_STARTSOURCE:     
                return "STARTSOURCE";

            case CTK_TOKEN_ENDSOURCE:       
                return "ENDSOURCE";

            default:
                return "";
        }
    }

    return ctk_token_names[kind];
}
