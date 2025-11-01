#include "ctk/lexer.h"
#include "ctk/token-list.h"
#include "ctk/text-context-writer.h"
#include <ctype.h>

#define TOKENLIST_OTHER(X) \
    X(NONE,         "none"), \
    X(IDENTIFIER,   "identifier"), \
    X(INTEGER,      "integer"), \
    X(ENDFILE,  "end-of-source"), \
    X(UNRECOGNIZED, "unrecognized")

#define TOKENLIST_KEYWORDS(X) \
    X(IF,           "if"), \
    X(THEN,         "then"), \
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

static void emit(ctk_lexer_t *lexer, ctk_tokenlist_t *toks, int kind) {
    static ctk_token_t tok;
    ctk_lexer_emit(lexer, &tok, kind);
    ctk_tokenlist_add(toks, &tok);
}

static bool is_id_start(uint32_t c) {
    return c < 256 && (isalpha(c) || c == '_');
}

static bool is_id_continue(uint32_t c) {
    return c < 256 && (isalnum(c) || c == '_');
}

static bool is_number(uint32_t c) {
    return c < 256 && isdigit(c);
}

static bool is_operator(uint32_t c) {
    return c == '+' || c == '-' || c == '>';
}

static bool is_whitespace(uint32_t c) {
    return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}

static void lex(ctk_lexer_t *lexer, ctk_tokenlist_t *toks) {
    emit(lexer, toks, CTK_TOKEN_STARTSOURCE);

    while (!ctk_lexer_at_eof(lexer)) {
        if (is_id_start(lexer->curr)) {
            do {
                ctk_lexer_advance(lexer);
            } while (is_id_continue(lexer->curr));

            tokenkind_t kind = ctk_lexer_lookup(lexer, keywords);
            emit(lexer, toks, kind == NONE ? IDENTIFIER : kind);
        } else if (is_number(lexer->curr)) {
            do {
                ctk_lexer_advance(lexer);
            } while (is_number(lexer->curr));

            emit(lexer, toks, IDENTIFIER);
        } else if (is_operator(lexer->curr)) {
            ctk_lexer_state_t state;
            tokenkind_t kind = UNRECOGNIZED;

            do {
                ctk_lexer_advance(lexer);

                tokenkind_t lkind = ctk_lexer_lookup(lexer, operators);
                if (lkind != NONE) {
                    ctk_lexer_save_state(lexer, &state);
                    kind = lkind;
                }
            } while (is_operator(lexer->curr));

            if (kind != UNRECOGNIZED) {
                ctk_lexer_restore_state(lexer, &state);
            }
            
            emit(lexer, toks, kind);
        } else if (is_whitespace(lexer->curr)) {
            do {
                ctk_lexer_advance(lexer);
            } while (is_whitespace(lexer->curr));

            ctk_lexer_discard(lexer);
            continue;
        } else if (lexer->curr == '#') {
            do {
                ctk_lexer_advance(lexer);
            } while (lexer->curr != '\n');

            ctk_lexer_discard(lexer);
            continue;
        } else {
            ctk_lexer_advance(lexer);
            emit(lexer, toks, UNRECOGNIZED);
        }
    }

    emit(lexer, toks, ENDFILE);
    emit(lexer, toks, CTK_TOKEN_ENDSOURCE);

    ctk_tokenlist_finalize(toks);
}

int main(void) {
    char *text = 
    "if 1 + 1 then  # comment\n"
    "  open\n"
    "else while x\n"
    "  return 1";

    ctk_textsrc_t src;
    ctk_textsrc_init_text(&src, "<test>", text);

    ctk_lexer_t lexer;
    ctk_lexer_init(&lexer, &src, ctk_decode_raw);

    ctk_tokenkind_set_name_table(names);

    ctk_tokenlist_t toks;
    ctk_tokenlist_init(&toks);

    lex(&lexer, &toks);

    for (size_t i = 0; i < toks.size; i++) {
        ctk_token_write(&toks.data[i], stderr);
        fprintf(stderr, "\n");
    }

    fprintf(stderr, "\n");

    ctk_textctx_style_t style = {
        .focus  = CTK_ANSI_FG_RED,
        .useansi = true,
    };

    for (size_t i = 0; i < toks.size; i++) {
        ctk_textctx_writer_t writer = {
            .style = &style,
            .focus = &toks.data[i],
        };
        
        ctk_textctk_write(&writer);
    }

    ctk_textsrc_destruct(&src);

    return 0;
}
