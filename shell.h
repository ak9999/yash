//
// Created by abdullah on 4/17/16.
//


/*
 * Info on colors found here:
 * https://stackoverflow.com/questions/3219393/stdlib-and-colored-output-in-c
 */
#ifndef SHELL_H
#define SHELL_H

// Disable warnings
#pragma GCC diagnostic ignored "-Wpointer-sign"

// Define colors
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

// Define deliminators.
#define TOKEN_DELIMS " \t\r\n\a"
// Define token's buffer size.
#define TOKEN_BUFSIZE 64

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

// UNIX includes
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pwd.h>

void print_red(char*);
void print_green(char*);
void print_yellow(char*);
void print_blue(char*);
void print_magenta(char*);
void print_cyan(char*);

void sigcatch();

void print_userhost(char*, char*, char*);

// Shell main loop functions.
void sh_loop(void);
char * sh_get_cmd(void);
char ** sh_tokenize_cmd(char*);
int sh_launch(char**);
int sh_execute(char**);

#include "shell.c"
#endif //SHELL_H
