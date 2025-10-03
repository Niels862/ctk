#include "text-decoder.h"

uint32_t ctk_decode_raw(ctk_strbuf_t *sb, size_t idx, uint32_t *size) {
    if (idx >= sb->size) {
        *size = 0;
        return CTK_DECODE_EOF;
    }

    *size = 1;
    return sb->data[idx];
}
