#include "string-span.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void ctk_strspan_init(ctk_strspan_t *span, char *start, char *end) {
    span->start = start;
    span->end = end;
}

void ctk_strspan_init_from_string(ctk_strspan_t *span, char *zs) {
    span->start = zs;
    span->end = zs + strlen(zs);
}

static void ctk_char_write_repr(char c, FILE *file) {
    if (isprint(c)) {
        fprintf(file, "%c", c);
    } else if (c < 10) {
        fprintf(file, "\\%d", c);
    } else {
        char *seq = NULL;

        switch (c) {
            case '\n':  seq = "\\n";    break;
            case '\r':  seq = "\\r";    break;
            case '\t':  seq = "\\t";    break;
            case '\\':  seq = "\\\\";   break;
            case '\"':  seq = "\\\"";   break;
        }

        if (seq == NULL) {
            fprintf(file, "\\%02X", c);
        } else {
            fputs(seq, file);
        }
    }
}

void ctk_strspan_write_repr(ctk_strspan_t *span, FILE *file) {
    fprintf(file, "\"");

    for (char *s = span->start; s != span->end; s++) {
        ctk_char_write_repr(*s, file);
    }

    fprintf(file, "\"");
}
