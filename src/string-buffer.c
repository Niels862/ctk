#include "string-buffer.h"
#include "alloc.h"
#include <string.h>
#include <assert.h>

static void ctk_strbuf_realloc(ctk_strbuf_t *sb, size_t min) {
    if (sb->cap < min) {
        while (sb->cap < min) {
            sb->cap *= 2;
        }

        sb->data = ctk_xrealloc(sb->data, sb->cap);
    }
}

void ctk_strbuf_init(ctk_strbuf_t *sb, size_t cap) {
    assert(cap > 0);

    sb->data = ctk_xmalloc(cap);
    sb->size = 0;
    sb->cap = cap;
}

void ctk_strbuf_destruct(ctk_strbuf_t *sb) {
    free(sb->data);
}

void ctk_strbuf_concat_str(ctk_strbuf_t *sb, char *s, size_t len) {
    if (sb->size + len < sb->cap) {
        ctk_strbuf_realloc(sb, sb->size + len);
    }

    memcpy(sb->data + sb->size, s, len);
    sb->size += len;
}
