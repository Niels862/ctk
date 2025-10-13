#ifndef CTK_STRING_BUFFER_H
#define CTK_STRING_BUFFER_H

#include "string-span.h"
#include "string-utils.h"
#include <stdio.h>
#include <stddef.h>

typedef struct {
    char *data;
    size_t size;
    size_t cap;
} ctk_strbuf_t;

void ctk_strbuf_init(ctk_strbuf_t *sb, size_t cap);

void ctk_strbuf_destruct(ctk_strbuf_t *sb);

void ctk_strbuf_concat_str(ctk_strbuf_t *sb, char *s, size_t len);

void ctk_strbuf_concat_file(ctk_strbuf_t *sb, FILE *file);

void ctk_strbuf_to_span(ctk_strbuf_t *sb, ctk_strspan_t *span);

#endif
