#ifndef CTK_SPAN_h
#define CTK_SPAN_H

typedef struct {
    void *start;
    void *end;
} ctk_span_t;

void ctk_span_init(ctk_span_t *span, void *start, void *end);

#endif
