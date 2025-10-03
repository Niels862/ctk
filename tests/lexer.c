#include "lexer.h"
#include <string.h>
#include <ctype.h>

void lex(ctk_lexer_t *lexer) {
    ctk_token_t tok;
    uint32_t *c = &lexer->curr;

    while (!ctk_lexer_at_eof(lexer)) {
        if (isalpha(*c) || *c == '_') {
            do {
                ctk_lexer_advance(lexer);
            } while (isalnum(*c));

            ctk_lexer_emit(lexer, &tok, 1);
        } else if (isdigit(*c)) {
            do {
                ctk_lexer_advance(lexer);
            } while (isdigit(*c));

            ctk_lexer_emit(lexer, &tok, 2);
        } else if (*c == '\n' || *c == '\r' || *c == ' ' || *c == '\t') {
            ctk_lexer_advance(lexer);
            ctk_lexer_discard(lexer);
            continue;
        } else {
            ctk_lexer_advance(lexer);
            ctk_lexer_emit(lexer, &tok, 3);
        }

        ctk_token_write(&tok, stderr);
        fprintf(stderr, "\n");
    }
}

int main() {
    char *text = "abc 123  $ a12\n  a1\n";

    ctk_textsrc_t src;
    ctk_textsrc_init_text(&src, "<test>", text);

    ctk_lexer_t lexer;
    ctk_lexer_init(&lexer, &src, ctk_decode_raw);

    char *names[] = {
        "null", "identifier", "integer", "unrecognized"
    };

    ctk_tokenkind_set_name_table(names);

    lex(&lexer);

    ctk_textsrc_destruct(&src);

    return 0;
}
