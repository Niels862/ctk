#include "ctk/rtti.h"
#include "ctk/alloc.h"
#include <stdint.h>

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

static void ctk_n_spaces(size_t n, FILE *file) {
    for (size_t i = 0; i < n; i++) {
        fputc(' ', file);
    }
}

static size_t ctk_rtti_total_n_attrs(ctk_rtti_t *meta) {
    size_t n = 0; 

    while (meta != NULL) {
        n += meta->attrs.n;
        meta = meta->super;
    }

    return n;
}

void ctk_rtti_write(void *obj, size_t depth, FILE *file) {
    ctk_rtti_t *meta = CTK_RTTI_META(obj);
    size_t n_attrs = ctk_rtti_total_n_attrs(meta);

    (void)n_attrs;

    fprintf(file, "%s\n", meta->name);

    size_t j = 0;
    while (meta != NULL) {        
        for (size_t i = 0; i < meta->attrs.n; i++, j++) {
            ctk_rtti_attr_t *attr = &meta->attrs.list[i];

            ctk_n_spaces(depth + 1, file);
            fprintf(file, "%s: ", attr->name);

            void *vp = (char *)obj + attr->offset;

            switch (attr->type) {
                case CTK_TYPE_INVALID:  
                    fprintf(file, "<invalid>\n");
                    break;

                case CTK_TYPE_RTTI:
                    ctk_rtti_write(vp, depth + 1, file);
                    fprintf(file, "\n");
                    break;

                case CTK_TYPE_I64:
                    fprintf(file, "%ld\n", *(int64_t *)vp);
                    break;

                case CTK_TYPE_BOOL:
                    fprintf(file, "%s\n", (*(bool *)vp) ? "true" : "false");
                    break;

                case CTK_TYPE_ZSTR:
                    fprintf(file, "%s\n", (char *)vp);
                    break;
            }
        }

        meta = meta->super;
    }
}
