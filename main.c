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

// STDC includes
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// UNIX includes
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
// Just in case it isn't defined.
#include <limits.h>

int main(void)
{
	pid_t pid; // stores process id

	/*if((pid = fork()) == -1) // System functions set errno.
	{
		perror("Process is a fork.");
		exit(EXIT_FAILURE);
	}*/

	const int MAX_LINE = 80;
	char * args[MAX_LINE/2 + 1]; // command line args
	bool should_run = true; // flag to determine when to exit program

	while(should_run)
	{
		char hostname[HOST_NAME_MAX + 1];
		char pathname[PATH_MAX + 1];
		struct passwd * p = getpwuid(getuid());
		if(p == NULL) // If we can't get the user_id we should quit.
		{
			fprintf(stderr, "Could not get username.\n");
			exit(EXIT_FAILURE);
		}

		// Set process effective ID to user ID.
		setreuid(getuid(), getuid());
		gethostname(hostname, sizeof(hostname)); // Get the hostname.
		char * username = p->pw_name;
		char * current_dir = getcwd(pathname, sizeof(pathname));
		/* Print prompt in the format:
		 * [username@hostname current_working_directory] % */
		printf("[%s@%s %s] %% ", username, hostname, current_dir);
		// Get input.
		if(getchar() == EOF) { should_run = false; }
		printf("\n");
		fflush(stdout); // Flush after input.

		/**
		* After reading user input, the steps are:
		* (1) fork a child process using fork()
		* (2) the child process will invoke execvp()
		* (3) if command included &, parent will invoke wait()
		*/
	}
	exit(EXIT_SUCCESS);
}
