#include "ctk/allocator.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void *ctk_xmalloc(size_t size) {
    void *p = malloc(size);

    if (p == NULL) {
        fprintf(stderr, "malloc(%zu) failed", size);
        abort();
    }

    return p;
}

void *ctk_xcalloc(size_t size) {
    void *p = calloc(1, size);

    if (p == NULL) {
        fprintf(stderr, "calloc(%zu) failed", size);
        abort();
    }

    return p;
}

void ctk_xrealloc(void *pp, size_t size) {
    void **vpp = pp;

    assert(vpp != NULL);
    assert(*vpp != NULL);

    void *p = realloc(*vpp, size);

    if (p == NULL) {
        fprintf(stderr, "realloc(-, %zu) failed", size);
        abort();
    }

    *vpp = p;
}

void ctk_free(void *pp) {
    void **vpp = pp;

    assert(vpp != NULL);

    if (*vpp != NULL) {
        free(*vpp);
    }

    *vpp = NULL;
}

void ctk_xfree(void *pp) {
    void **vpp = pp;

    assert(vpp != NULL);
    assert(*vpp != NULL);

    free(*vpp);

    *vpp = NULL;
}
