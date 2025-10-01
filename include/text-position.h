#ifndef CTK_TEXT_POSITION_H
#define CTK_TEXT_POSITION_H

typedef struct {
    int line;
    int col;
} ctk_textpos_t;

void ctk_textpos_init(ctk_textpos_t *pos);

void ctk_textpos_copy(ctk_textpos_t *dst, 
                      ctk_textpos_t *src);

#endif