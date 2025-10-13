#include "ctk/text-source.h"
#include <stddef.h>
#include <stdio.h>
#include <assert.h>

static void test_read(char *name) {
    FILE *file = fopen(name, "r");

    assert(file != NULL);

    ctk_textsrc_t ts;
    ctk_textsrc_init_file(&ts, name, file);

    ctk_textsrc_write(&ts, stdout);

    ctk_textsrc_destruct(&ts);

    fclose(file);
}

int main() {
    char *names[] = {
        "tests/fileread.c",
        NULL,
    };

    for (size_t i = 0; names[i] != NULL; i++) {
        test_read(names[i]);
    }

    return 0;
}
