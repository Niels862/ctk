#include "ctk/string-buffer.h"
#include "ctk/allocator.h"
#include <string.h>
#include <assert.h>

static void ctk_strbuf_realloc(ctk_strbuf_t *sb, size_t min) {
    if (sb->cap < min) {
        while (sb->cap < min) {
            sb->cap *= 2;
        }

        ctk_xrealloc(&sb->data, sb->cap);
    }
}

void ctk_strbuf_init(ctk_strbuf_t *sb, size_t cap) {
    assert(cap > 0);

    sb->data = ctk_xmalloc(cap);
    sb->size = 0;
    sb->cap = cap;
}

void ctk_strbuf_destruct(ctk_strbuf_t *sb) {
    ctk_xfree(&sb->data);
}

void ctk_strbuf_concat_str(ctk_strbuf_t *sb, char *s, size_t len) {
    if (sb->size + len < sb->cap) {
        ctk_strbuf_realloc(sb, sb->size + len);
    }

    memcpy(sb->data + sb->size, s, len);
    sb->size += len;
}

void ctk_strbuf_concat_file(ctk_strbuf_t *sb, FILE *file) {
    size_t readsize = 256;
    ctk_strbuf_realloc(sb, sb->size + readsize);

    size_t nread;
    while ((nread = fread(sb->data + sb->size, 1, readsize, file)) > 0) {
        sb->size += nread;
        readsize *= 2;
        ctk_strbuf_realloc(sb, sb->size + readsize);
    }
}

void ctk_strbuf_to_span(ctk_strbuf_t *sb, ctk_strspan_t *span) {
    ctk_strspan_init(span, sb->data, sb->data + sb->size);
}
