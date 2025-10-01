#include "text-position.h"

void ctk_textpos_init(ctk_textpos_t *pos) {
    pos->line = 1;
    pos->col = 1;
}

void ctk_textpos_copy(ctk_textpos_t *dst, 
                      ctk_textpos_t *src) {
    dst->line = src->line;
    dst->col = src->col;
}
