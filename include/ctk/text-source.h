#ifndef CTK_TEXT_SOURCE_H
#define CTK_TEXT_SOURCE_H

#include "ctk/string-buffer.h"
#include "ctk/string-utils.h"
#include <stdio.h>
#include <stddef.h>

typedef struct {
    ctk_zstr_t name;
    ctk_strbuf_t text;
} ctk_textsrc_t;

void ctk_textsrc_init_text(ctk_textsrc_t *ts, ctk_zstr_t name, 
                           ctk_zstr_t text);

void ctk_textsrc_init_file(ctk_textsrc_t *ts, ctk_zstr_t name, FILE *file);

void ctk_textsrc_destruct(ctk_textsrc_t *ts);

void ctk_textsrc_write(ctk_textsrc_t *ts, FILE *file);

#endif
