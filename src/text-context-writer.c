#include "ctk/text-context-writer.h"
#include <stdio.h>

char const *ctk_find_line_start();

void ctk_textctk_write(ctk_textctx_writer_t *writer) {
    fputs(writer->style->focus, stderr);

    ctk_str_write(writer->focus->lexeme.start, writer->focus->lexeme.end, stderr);

    fputs(CTK_ANSI_RESET "\n", stderr);
}
