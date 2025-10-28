#include "ctk/span.h"

void ctk_span_init(ctk_span_t *span, void *start, void *end) {
    span->start = start;
    span->end = end;
}