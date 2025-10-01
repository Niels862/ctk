#include "alloc.h"
#include <stdlib.h>
#include <stdio.h>

void *ctk_xmalloc(size_t size) {
    void *p = malloc(size);

    if (p == NULL) {
        perror("malloc");
        abort();
    }

    return p;
}

void *ctk_xcalloc(size_t size) {
    void *p = calloc(1, size);

    if (p == NULL) {
        perror("calloc");
        abort();
    }

    return p;
}

void *ctk_xrealloc(void *p, size_t size) {
    void *p2 = realloc(p, size);

    if (p2 == NULL) {
        perror("realloc");
        abort();
    }

    return p2;
}
