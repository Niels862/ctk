#include "ctk/token.h"
#include "ctk/text-source.h"

int main(void) {
    ctk_textsrc_t src;
    ctk_textsrc_init_text(&src, "<test>", "test");

    ctk_textpos_t pos;
    ctk_textpos_init(&pos);

    ctk_strspan_t lexeme;
    ctk_strspan_init(&lexeme, src.text.data, src.text.data + 4);

    ctk_token_t tok;
    ctk_token_init(&tok, 1, &src, &pos, &lexeme);

    ctk_token_write(&tok, stdout);
    fprintf(stdout, "\n");

    char *names[] = {
        "null",
        "identifier"
    };

    ctk_tokenkind_set_name_table(names);

    ctk_token_write(&tok, stdout);
    fprintf(stdout, "\n");

    return 0;
}