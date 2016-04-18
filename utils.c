//
// Created by abdullah on 4/17/16.
//

#include "utils.h"

void print_red(char * string)
{
    printf(ANSI_COLOR_RED "%s" ANSI_COLOR_RESET, string);
}

void print_green(char * string)
{
    printf(ANSI_COLOR_GREEN "%s" ANSI_COLOR_RESET, string);
}

void print_yellow(char * string)
{
    printf(ANSI_COLOR_YELLOW "%s" ANSI_COLOR_RESET, string);
}

void print_blue(char * string)
{
    printf(ANSI_COLOR_BLUE "%s" ANSI_COLOR_RESET, string);
}

void print_magenta(char * string)
{
    printf(ANSI_COLOR_MAGENTA "%s" ANSI_COLOR_RESET, string);
}

void print_cyan(char * string)
{
    printf(ANSI_COLOR_CYAN "%s" ANSI_COLOR_RESET, string);
}

void print_userhost(char * username, char * hostname, char * current_dir)
{
    printf(ANSI_COLOR_CYAN "[" ANSI_COLOR_RESET);
    print_blue(username);
    printf(ANSI_COLOR_BLUE "@" ANSI_COLOR_RESET);
    print_blue(hostname);
    printf(" ");
    print_green(current_dir);
    printf(ANSI_COLOR_CYAN "]" ANSI_COLOR_RESET);
    printf(" %% ");
}
