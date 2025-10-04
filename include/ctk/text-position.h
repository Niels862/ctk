#ifndef CTK_TEXT_POSITION_H
#define CTK_TEXT_POSITION_H

#include <stdbool.h>

typedef struct {
    int line;
    int col;
} ctk_textpos_t;

void ctk_textpos_init(ctk_textpos_t *pos);

void ctk_textpos_next(ctk_textpos_t *pos, bool newline);

#endif