/*
* Author: Abdullah Khan
* Date: 2016-04-16
* Program: yash - yet another shell
* Description: An alternative shell.
* Build instructions: TBA
*/

/* If using a compiler that defaults to C99 or later */
#if __STDC_VERSION__ >= 199901L
#define _XOPEN_SOURCE 700
#else
#define _XOPEN_SOURCE 600
#endif /* __STDC_VERSION__ */

// Utilities
#include "shell.h"

int main(void)
{
	signal(SIGINT, SIG_IGN); // Ignore Ctrl-C.
	sh_loop();

	return EXIT_SUCCESS;
}
