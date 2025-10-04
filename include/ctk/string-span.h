#ifndef CTK_STRING_SPAN_H
#define CTK_STRING_SPAN_H

#include <stdio.h>

typedef struct {
    char *start;
    char *end;
} ctk_strspan_t;

void ctk_strspan_init(ctk_strspan_t *span, char *start, char *end);

void ctk_strspan_init_from_string(ctk_strspan_t *span, char *zs);

void ctk_strspan_write_repr(ctk_strspan_t *span, FILE *file);

#endif
