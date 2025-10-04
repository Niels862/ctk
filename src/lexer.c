#include "ctk/lexer.h"
#include <string.h>
#include <assert.h>

static void ctk_lexer_state_init(ctk_lexer_state_t *state) {
    ctk_textpos_init(&state->pos);
    state->idx = 0;
}

static void ctk_lexer_read_codepoint(ctk_lexer_t *lexer) {
    lexer->curr = lexer->decoder(&lexer->src->text, 
                                 lexer->currstate.idx, 
                                 &lexer->currsize);
}

void ctk_lexer_init(ctk_lexer_t *lexer, ctk_textsrc_t *src, 
                    ctk_decoder_t decoder) {
    lexer->src = src;
    ctk_lexer_state_init(&lexer->basestate);
    ctk_lexer_state_init(&lexer->currstate);
    lexer->decoder = decoder;

    ctk_lexer_read_codepoint(lexer);
}

void ctk_lexer_advance(ctk_lexer_t *lexer) {
    assert(!ctk_lexer_at_eof(lexer));
    assert(!CTK_DECODER_IS_ERROR(lexer->curr));

    ctk_textpos_next(&lexer->currstate.pos, lexer->curr == '\n');
    lexer->currstate.idx += lexer->currsize;
    
    ctk_lexer_read_codepoint(lexer);
}

bool ctk_lexer_at_eof(ctk_lexer_t *lexer) {
    assert(lexer->currstate.idx <= lexer->src->text.size);
    return lexer->currstate.idx >= lexer->src->text.size;
}

void ctk_lexer_emit(ctk_lexer_t *lexer, ctk_token_t *tok, int kind) {
    ctk_strspan_t lexeme;
    ctk_lexer_to_span(lexer, &lexeme);

    ctk_token_init(tok, kind, lexer->src, &lexer->basestate.pos, &lexeme);

    lexer->basestate = lexer->currstate;
}

void ctk_lexer_discard(ctk_lexer_t *lexer) {
    lexer->basestate = lexer->currstate;
}

void ctk_lexer_to_span(ctk_lexer_t *lexer, ctk_strspan_t *dst) {
    dst->start = &lexer->src->text.data[lexer->basestate.idx];
    dst->end   = &lexer->src->text.data[lexer->currstate.idx];
}

void ctk_lexer_save_state(ctk_lexer_t *lexer, ctk_lexer_state_t *state) {
    *state = lexer->currstate;
}

void ctk_lexer_restore_state(ctk_lexer_t *lexer, ctk_lexer_state_t *state) {
    lexer->currstate = *state;
    ctk_lexer_read_codepoint(lexer);
}

int ctk_lexer_lookup(ctk_lexer_t *lexer, 
                                  ctk_fixed_lexeme_t lexs[]) {
    ctk_strspan_t span;
    ctk_lexer_to_span(lexer, &span);
    
    size_t len = span.end - span.start;
    int match = 0;

    for (size_t i = 0; lexs[i].kind != 0; i++) {
        ctk_fixed_lexeme_t *lex = &lexs[i];
        if (strncmp(span.start, lex->lexeme, len) == 0 
                && lex->lexeme[len] == '\0') {
            match = lexs[i].kind;
        }
    }

    return match;
}

int ctk_lexer_lookup_longest(ctk_lexer_t *lexer, 
                                          ctk_fixed_lexeme_t lexs[]) {
    ctk_strspan_t span;
    ctk_lexer_to_span(lexer, &span);
    
    size_t len = span.end - span.start;

    size_t longest = 0;
    int match = 0;

    for (size_t i = 0; lexs[i].kind != 0; i++) {
        ctk_fixed_lexeme_t *lex = &lexs[i];

        size_t matchsize = 0;
        for (size_t j = 0; j < len && lex->lexeme[j] != '\0'; j++) {
            if (span.start[j] == lex->lexeme[j]) {
                matchsize++;
            }
        }

        if (matchsize > longest) {
            longest = matchsize;
            match = lex->kind;
        }
    }

    return match;
}
