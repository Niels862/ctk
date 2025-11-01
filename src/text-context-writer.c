#include "ctk/text-context-writer.h"
#include <stdio.h>

static void ctk_write_ansi_esc(ctk_ansi_esc_t ansi, bool useansi) {
    if (useansi && ansi != NULL) {
        fputs(ansi, stderr);
    }
}

static char const *ctk_find_line_start(char const *s) {
    while (*s != '\n') {
        s--;
    }
    return s + 1;
}

static char const *ctk_find_line_end(char const *s) {
    while (*s != '\n') {
        s++;
    }
    return s;
}

static void ctk_chars_write(char c, size_t n) {
    for (size_t i = 0; i < n; i++) {
        fputc(c, stderr);
    }
}

static void ctk_marker_write(ctk_textctx_style_t const *style, 
                             size_t start, size_t len) {
    ctk_chars_write(' ', start);
    
    ctk_write_ansi_esc(style->marker, style->useansi);

    if (len > 0) {
        fputc(style->markstart, stderr);
    }

    if (len > 2) {
        ctk_chars_write(style->markinter, len - 2);
    }

    if (len > 1) {
        fputc(style->markend, stderr);
    }

    ctk_write_ansi_esc(CTK_ANSI_RESET, style->useansi);
    fprintf(stderr, "\n");
}

void ctk_textctk_write(ctk_textctx_writer_t *writer) {
    ctk_textctx_style_t const *style = writer->style;

    ctk_strspan_t *focus = &writer->focus->lexeme;

    if (focus->start == focus->end) {
        ctk_write_ansi_esc(CTK_ANSI_BG_BRIGHT(CTK_ANSI_BLUE), style->useansi);
        fprintf(stderr, "(skipped)");
        ctk_write_ansi_esc(CTK_ANSI_RESET, style->useansi);
        fprintf(stderr, "\n");
        return;
    }

    char const *start = ctk_find_line_start(focus->start);
    char const *end   = ctk_find_line_end(focus->end);

    ctk_str_write(start, focus->start, stderr);

    ctk_write_ansi_esc(style->focus, style->useansi);
    ctk_str_write(focus->start, focus->end, stderr);
    ctk_write_ansi_esc(CTK_ANSI_RESET, style->useansi);

    ctk_str_write(focus->end, end, stderr);
    fprintf(stderr, "\n");

    if (writer->style->usemarker) {
        ctk_marker_write(style, 
                         focus->start - start, 
                         focus->end - focus->start);
    }
}
