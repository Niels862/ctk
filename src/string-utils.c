#include "ctk/string-utils.h"
#include "ctk/allocator.h"
#include <string.h>
#include <assert.h>

ctk_zstr_t ctk_strdup(ctk_zstr_t s) {
    size_t len = strlen(s);
    ctk_zstr_t s2 = ctk_xmalloc(len);
    memcpy(s2, s, len + 1);
    return s2;
}

void ctk_str_write(char const *start, char const *end, FILE *file) {
    assert(start <= end);
    
    if (start == end) {
        return;
    }

    int len = (int)(end - start);
    fprintf(file, "%.*s", len, start);
}