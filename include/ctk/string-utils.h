#ifndef CTK_STRING_UTILS_H
#define CTK_STRING_UTILS_H

#include <stdio.h>

typedef char *ctk_zstr_t;

ctk_zstr_t ctk_strdup(ctk_zstr_t s);

void ctk_str_write(char const *start, char const *end, FILE *file);

#endif
