#include "ctk/lexer.h"
#include <string.h>
#include <ctype.h>

#define TOKENLIST_OTHER(X) \
    X(NONE,         "none"), \
    X(IDENTIFIER,   "identifier"), \
    X(INTEGER,      "integer"), \
    X(ENDOFSOURCE,  "end-of-source"), \
    X(UNRECOGNIZED, "unrecognized")

#define TOKENLIST_KEYWORDS(X) \
    X(IF,           "if"), \
    X(WHILE,        "while"), \
    X(FOR,          "for") \

#define TOKENLIST_OPERATORS(X) \
    X(PLUS,         "+"), \
    X(MINUS,        "-"), \
    X(RSHIFT,       ">>") \

#define X_EXPAND_ENUM(e, s) e

typedef enum {
    TOKENLIST_OTHER(X_EXPAND_ENUM),
    TOKENLIST_KEYWORDS(X_EXPAND_ENUM),
    TOKENLIST_OPERATORS(X_EXPAND_ENUM),
} tokenkind_t;

#define X_EXPAND_NAMES(e, s) [e] = s

static char *names[] = {
    TOKENLIST_OTHER(X_EXPAND_NAMES),
    TOKENLIST_KEYWORDS(X_EXPAND_NAMES),
    TOKENLIST_OPERATORS(X_EXPAND_NAMES),
};

#define X_EXPAND_FIXED(e, s) { s, e }

static ctk_fixed_lexeme_t keywords[] = {
    TOKENLIST_KEYWORDS(X_EXPAND_FIXED),
    { 0 },
};

static ctk_fixed_lexeme_t operators[] = {
    TOKENLIST_OPERATORS(X_EXPAND_FIXED),
    { 0 },
};

static bool isoperator(uint32_t c) {
    return c == '+' || c == '-' || c == '>';
}

static bool iswhitespace(uint32_t c) {
    return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}

static void lex(ctk_lexer_t *lexer) {
    ctk_token_t tok;
    uint32_t *c = &lexer->curr;

    while (!ctk_lexer_at_eof(lexer)) {
        if (isalpha(*c) || *c == '_') {
            do {
                ctk_lexer_advance(lexer);
            } while (isalnum(*c));

            tokenkind_t kind = ctk_lexer_lookup(lexer, keywords);
            ctk_lexer_emit(lexer, &tok, kind == NONE ? IDENTIFIER : kind);
        } else if (isdigit(*c)) {
            do {
                ctk_lexer_advance(lexer);
            } while (isdigit(*c));

            ctk_lexer_emit(lexer, &tok, IDENTIFIER);
        } else if (isoperator(*c)) {
            ctk_lexer_state_t state;
            tokenkind_t kind = UNRECOGNIZED;

            do {
                ctk_lexer_advance(lexer);

                tokenkind_t lkind = ctk_lexer_lookup(lexer, operators);
                if (lkind != NONE) {
                    ctk_lexer_save_state(lexer, &state);
                    kind = lkind;
                }
            } while (isoperator(*c));

            if (kind != UNRECOGNIZED) {
                ctk_lexer_restore_state(lexer, &state);
            }
            
            ctk_lexer_emit(lexer, &tok, kind);
        } else if (iswhitespace(*c)) {
            do {
                ctk_lexer_advance(lexer);
            } while (iswhitespace(*c));

            ctk_lexer_discard(lexer);
            continue;
        } else {
            ctk_lexer_advance(lexer);
            ctk_lexer_emit(lexer, &tok, UNRECOGNIZED);
        }

        ctk_token_write(&tok, stderr);
        fprintf(stderr, "\n");
    }

    ctk_lexer_emit(lexer, &tok, ENDOFSOURCE);

    ctk_token_write(&tok, stderr);
    fprintf(stderr, "\n");
}

int main() {
    char *text = "abc 123 for +$-->> > a12\n while1 a1\n";

    ctk_textsrc_t src;
    ctk_textsrc_init_text(&src, "<test>", text);

    ctk_lexer_t lexer;
    ctk_lexer_init(&lexer, &src, ctk_decode_raw);

    ctk_tokenkind_set_name_table(names);

    lex(&lexer);

    ctk_textsrc_destruct(&src);

    return 0;
}
