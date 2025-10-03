#include "lexer.h"
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
    char *start = &lexer->src->text.data[lexer->basestate.idx];
    char *end   = &lexer->src->text.data[lexer->currstate.idx];

    ctk_strspan_t lexeme;
    ctk_strspan_init(&lexeme, start, end);

    ctk_token_init(tok, kind, lexer->src, &lexer->basestate.pos, &lexeme);

    lexer->basestate = lexer->currstate;
}

void ctk_lexer_discard(ctk_lexer_t *lexer) {
    lexer->basestate = lexer->currstate;
}


