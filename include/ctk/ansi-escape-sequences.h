#ifndef CTK_ANSI_ESCAPE_SEQUENCES_H
#define CTK_ANSI_ESCAPE_SEQUENCES_H

typedef char const *ctk_ansi_esc_t;

#define CTK_ANSI_ESCAPE(e)      ("\033[" e "m")

#define CTK_ANSI_RESET          CTK_ANSI_ESCAPE("0")

#define CTK_ANSI_BLACK          "0"
#define CTK_ANSI_RED            "1"
#define CTK_ANSI_GREEN          "2"
#define CTK_ANSI_YELLOW         "3"
#define CTK_ANSI_BLUE           "4"
#define CTK_ANSI_MAGENTA        "5"
#define CTK_ANSI_CYAN           "6"
#define CTK_ANSI_WHITE          "7"

#define CTK_ANSI_FG_DARK(c)     CTK_ANSI_ESCAPE("3" c)
#define CTK_ANSI_FG_BRIGHT(c)   CTK_ANSI_ESCAPE("9" c)
#define CTK_ANSI_BG_DARK(c)     CTK_ANSI_ESCAPE("4" c)
#define CTK_ANSI_BG_BRIGHT(c)   CTK_ANSI_ESCAPE("10" c)

#endif
