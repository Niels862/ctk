#include "ctk/rtti.h"
#include "ctk/alloc.h"

ctk_rtti_t ctk_rtti_base = {
    .super = NULL,
    .name = "(base)",
};

void ctk_rtti_delete(void *obj) {
    ctk_rtti_t *meta = CTK_RTTI_META(obj);
    (void)meta;

    free(obj);
}

bool ctk_rtti_instanceof(void *obj, ctk_rtti_t *meta) {
    ctk_rtti_t *imeta = CTK_RTTI_META(obj);

    while (imeta != NULL) {
        if (imeta == meta) {
            return true;
        }

        imeta = imeta->super;
    }

    return false;
}

void *ctk_rtti_dyncast(void *obj, ctk_rtti_t *meta) {
    if (ctk_rtti_instanceof(obj, meta)) {
        return obj;
    }

    return NULL;
}
