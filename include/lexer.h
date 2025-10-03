#ifndef CTK_LEXER_H
#define CTK_LEXER_H

#include "token.h"
#include "text-source.h"
#include "text-decoder.h"
#include <stdint.h>

typedef struct {
    ctk_textpos_t pos;
     /* Index into src.text */
    size_t idx;
} ctk_lexer_state_t;

typedef struct {
    ctk_textsrc_t *src;
    ctk_lexer_state_t basestate;
    ctk_lexer_state_t currstate;
    ctk_decoder_t decoder;

    uint32_t curr;
    uint32_t currsize;
} ctk_lexer_t;

void ctk_lexer_init(ctk_lexer_t *lexer, ctk_textsrc_t *src, 
                    ctk_decoder_t decoder);

void ctk_lexer_advance(ctk_lexer_t *lexer);

bool ctk_lexer_at_eof(ctk_lexer_t *lexer);

void ctk_lexer_emit(ctk_lexer_t *lexer, ctk_token_t *tok, int kind);

void ctk_lexer_discard(ctk_lexer_t *lexer);

uint32_t ctk_lexer_codepoint(ctk_lexer_t *lexer);

#endif
