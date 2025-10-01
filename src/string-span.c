#include "string-span.h"
#include <stdio.h>
#include <string.h>

void ctk_strspan_init(ctk_strspan_t *span, char *start, char *end) {
    span->start = start;
    span->end = end;
}

void ctk_strspan_init_from_string(ctk_strspan_t *span, char *zs) {
    span->start = zs;
    span->end = zs + strlen(zs);
}

void ctk_strspan_copy(ctk_strspan_t *dst, ctk_strspan_t *src) {
    dst->start = src->start;
    dst->end = src->end;
}

void ctk_strspan_write_repr(ctk_strspan_t *span, FILE *file) {
    fprintf(file, "\"");

    for (char *s = span->start; s != span->end; s++) {
        char c = *s;

        /* FIXME: add unprintable characters */
        fprintf(file, "%c", c);
    }

    fprintf(file, "\"");
}
