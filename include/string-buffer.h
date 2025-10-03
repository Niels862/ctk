#ifndef CTK_STRING_BUFFER_H
#define CTK_STRING_BUFFER_H

#include <stddef.h>

/* Does not assume strings are zero-terminated. 
 * 
 */
typedef struct {
    char *data;
    size_t size;
    size_t cap;
} ctk_strbuf_t;

void ctk_strbuf_init(ctk_strbuf_t *sb, size_t cap);

void ctk_strbuf_destruct(ctk_strbuf_t *sb);

void ctk_strbuf_concat_str(ctk_strbuf_t *sb, char *s, size_t len);

#endif
