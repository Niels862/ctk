#ifndef CTK_TEXT_DECODER_H
#define CTK_TEXT_DECODER_H

#include "ctk/string-buffer.h"
#include <stdint.h>

typedef enum {
    CTK_DECODE_EOF = 0x110000,
    CTK_DECODE_ERROR,
} ctk_decoder_result_t;

typedef struct {
    uint32_t result;
    uint32_t size;
} ctk_decoder_value_t;

#define CTK_DECODER_IS_ERROR(c) ((c) >= CTK_DECODE_EOF)

typedef uint32_t(*ctk_decoder_t)(ctk_strbuf_t *sb, size_t idx, uint32_t *size);

uint32_t ctk_decode_raw(ctk_strbuf_t *sb, size_t idx, uint32_t *size);

#endif
