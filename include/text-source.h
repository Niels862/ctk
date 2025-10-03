#ifndef CTK_TEXT_SOURCE_H
#define CTK_TEXT_SOURCE_H

#include "string-buffer.h"
#include "string-utils.h"
#include <stddef.h>

typedef struct {
    ctk_zstr_t name;
    ctk_strbuf_t text;
} ctk_textsrc_t;

void ctk_textsrc_init_text(ctk_textsrc_t *ts, ctk_zstr_t name, 
                           ctk_zstr_t s);

void ctk_textsrc_destruct(ctk_textsrc_t *ts);

#endif
