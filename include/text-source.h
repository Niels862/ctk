#ifndef CTK_TEXT_SOURCE_H
#define CTK_TEXT_SOURCE_H

typedef struct {
    char *name;
    char *text;
} ctk_textsrc_t;

void ctk_textsrc_init(ctk_textsrc_t *ts, char *name, char *text);

#endif
