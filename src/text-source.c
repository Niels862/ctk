#include "ctk/text-source.h"
#include <string.h>

void ctk_textsrc_init_text(ctk_textsrc_t *ts, ctk_zstr_t name, 
                           ctk_zstr_t text) {
    ts->name = name;

    size_t size = strlen(text);
    ctk_strbuf_init(&ts->text, size);
    ctk_strbuf_concat_str(&ts->text, text, size);
}

void ctk_textsrc_destruct(ctk_textsrc_t *ts) {
    ctk_strbuf_destruct(&ts->text);
}
