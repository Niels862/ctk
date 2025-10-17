#include "ctk/rtti.h"
#include "ctk/allocator.h"
#include <stdint.h>

ctk_rtti_t ctk_rtti_base = {
    .super = NULL,
    .name = "(base)",
};

static void *ctk_get_static_attr(void *obj, size_t offset) {
    return (void *)((char *)obj + offset);
}

static void *ctk_get_pointer_attr(void *obj, size_t offset) {
    return *(void **)ctk_get_static_attr(obj, offset);
}

void ctk_rtti_delete(void *obj) {
    if (obj == NULL) {
        return;
    }

    ctk_rtti_t *meta = CTK_RTTI_META(obj);
    
    for (size_t i = 0; meta->attrs[i].offset > 0; i++) {
        ctk_rtti_attr_t *attr = &meta->attrs[i];

        switch (attr->type) {
            case CTK_TYPE_RTTI: {
                void *subobj = ctk_get_pointer_attr(obj, attr->offset);
                ctk_rtti_delete(subobj);
                break;
            }

            case CTK_TYPE_RTTI_LIST: {
                void **list = ctk_get_pointer_attr(obj, attr->offset);
                ctk_rtti_list_delete(list);
                break;
            }

            default:
                break;
        }
    }

    ctk_xfree(&obj);
}

void ctk_rtti_list_delete(void **list) {
    if (list == NULL) {
        return;
    }
    
    for (size_t i = 0; list[i] != NULL; i++) {
        ctk_rtti_delete(list[i]);
    }

    ctk_xfree(&list);
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
    for (size_t i = 0; i < 2 * n; i++) {
        fputc(' ', file);
    }
}

static void ctk_rtti_attr_write(void *obj, ctk_rtti_attr_t *attr, size_t depth, FILE *file) {
    ctk_n_spaces(depth + 1, file);
    fprintf(file, "%s: ", attr->name);

    switch (attr->type) {
        case CTK_TYPE_INVALID:  
            fprintf(file, "<invalid>\n");
            break;

        case CTK_TYPE_RTTI: {
            void *subobj = ctk_get_pointer_attr(obj, attr->offset);
            ctk_rtti_write(subobj, depth + 1, file);
            fprintf(file, "\n");
            break;
        }

        case CTK_TYPE_RTTI_LIST: {
            void **list = ctk_get_pointer_attr(obj, attr->offset);
            fprintf(file, "[\n");

            for (size_t i = 0; list[i] != NULL; i++) {
                ctk_n_spaces(depth + 2, file);
                fprintf(file, "[%ld]: ", i);
                ctk_rtti_write(list[i], depth + 2, file);
            }

            ctk_n_spaces(depth + 1, file);
            fprintf(file, "]\n");
            break;
        }

        case CTK_TYPE_I64: {
            int64_t i64 = *(int64_t *)ctk_get_static_attr(obj, attr->offset);
            fprintf(file, "%ld\n", i64);
            break;
        }

        case CTK_TYPE_BOOL: {
            bool b = *(bool *)ctk_get_static_attr(obj, attr->offset);
            fprintf(file, "%s\n", b ? "true" : "false");
            break;
        }

        case CTK_TYPE_ZSTR: {
            ctk_zstr_t zstr = ctk_get_pointer_attr(obj, attr->offset);
            fprintf(file, "%s\n", zstr);
            break;
        }
    }
}

void ctk_rtti_write(void *obj, size_t depth, FILE *file) {
    ctk_rtti_t *meta = CTK_RTTI_META(obj);

    fprintf(file, "%s\n", meta->name);

    size_t j = 0;
    while (meta != NULL) {        
        for (size_t i = 0; meta->attrs[i].offset > 0; i++, j++) {
            ctk_rtti_attr_t *attr = &meta->attrs[i];
            ctk_rtti_attr_write(obj, attr, depth, file);
        }

        meta = meta->super;
    }
}
