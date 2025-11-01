#ifndef CTK_TEXT_CONTEXT_WRITER_H
#define CTK_TEXT_CONTEXT_WRITER_H

#include "token.h"
#include "ansi-escape-sequences.h"
#include <stdbool.h>

typedef struct {
    bool useansi;
    bool usemarker;

    char markstart;
    char markinter;
    char markend;

    
    ctk_ansi_esc_t focus;
    ctk_ansi_esc_t marker;
} ctk_textctx_style_t;

typedef struct {
    ctk_textctx_style_t const *style;
    ctk_token_t *focus;
} ctk_textctx_writer_t;

void ctk_textctk_write(ctk_textctx_writer_t *writer);

#endif
