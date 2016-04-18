//
// Created by abdullah on 4/17/16.
//


/*
 * Info on colors found here:
 * https://stackoverflow.com/questions/3219393/stdlib-and-colored-output-in-c
 */
#ifndef YASH_UTILS_H
#define YASH_UTILS_H

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#include <stdlib.h>
#include <stdio.h>

void print_red(char*);
void print_green(char*);
void print_yellow(char*);
void print_blue(char*);
void print_magenta(char*);
void print_cyan(char*);

void print_userhost(char*, char*, char*);

#endif //YASH_UTILS_H
