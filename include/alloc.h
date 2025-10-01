#ifndef CTK_UTILS_H
#define CTK_UTILS_H

#include <stdlib.h> // to expose free()

void *ctk_xmalloc(size_t size);

void *ctk_xcalloc(size_t size);

void *ctk_xrealloc(void *p, size_t size);

#endif
