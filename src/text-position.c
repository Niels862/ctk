#include "ctk/text-position.h"

void ctk_textpos_init(ctk_textpos_t *pos) {
    pos->line = 1;
    pos->col = 1;
}

void ctk_textpos_next(ctk_textpos_t *pos, bool newline) {
    if (newline) {
        pos->line++;
        pos->col = 1;
    } else {
        pos->col++;
    }
}
