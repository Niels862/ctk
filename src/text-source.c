#include "text-source.h"

void ctk_textsrc_init(ctk_textsrc_t *ts, char *name, char *text) {
    ts->name = name;
    ts->text = text;
}
