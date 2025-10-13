#include "ctk/text-source.h"
#include "ctk/string-span.h"
#include <string.h>

void ctk_textsrc_init_text(ctk_textsrc_t *ts, ctk_zstr_t name, 
                           ctk_zstr_t text) {
    ts->name = name;

    size_t size = strlen(text);
    ctk_strbuf_init(&ts->text, size);
    ctk_strbuf_concat_str(&ts->text, text, size);
}

void ctk_textsrc_init_file(ctk_textsrc_t *ts, ctk_zstr_t name, FILE *file) {
    ts->name = name;

    ctk_strbuf_init(&ts->text, 256);
    ctk_strbuf_concat_file(&ts->text, file);
}

void ctk_textsrc_destruct(ctk_textsrc_t *ts) {
    ctk_strbuf_destruct(&ts->text);
}

void ctk_textsrc_write(ctk_textsrc_t *ts, FILE *file) {
    fprintf(file, "%s: ", ts->name);

    ctk_strspan_t span;
    ctk_strbuf_to_span(&ts->text, &span);

    ctk_strspan_write_repr(&span, file);

    fprintf(file, "\"\n");
}
