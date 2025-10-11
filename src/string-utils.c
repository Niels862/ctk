#include "ctk/string-utils.h"
#include "ctk/allocator.h"
#include <string.h>

ctk_zstr_t ctk_strdup(ctk_zstr_t s) {
    size_t len = strlen(s);
    ctk_zstr_t s2 = ctk_xmalloc(len);
    memcpy(s2, s, len + 1);
    return s2;
}
