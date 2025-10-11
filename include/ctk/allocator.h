#ifndef CTK_UTILS_H
#define CTK_UTILS_H

#include <stddef.h>

void *ctk_xmalloc(size_t size);

void *ctk_xcalloc(size_t size);

void ctk_xrealloc(void *pp, size_t size);

void ctk_free(void *pp);

void ctk_xfree(void *pp);

#endif
