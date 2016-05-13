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

// Utilities
#include "utils.h"

// Define deliminators.
#define DELIMINATORS " \t\r\n"

int main(void)
{
	const int MAX_LINE = 256;
	char *line;
	char command[MAX_LINE]; // command
	char *cmd; // Parse command with this!

	while(1)
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
		 * [username@hostname current_working_directory] %
		 */
		print_userhost(username, hostname, current_dir);
		// Get input.
		if(!fgets(command, MAX_LINE, stdin)) { break; }
		line = strdup(command);

		//Parse and execute
		if((cmd = strtok(command, DELIMINATORS)))
		{
			// 'cd' is a shell built-in.
			if(strcmp(cmd, "cd") == 0)
			{
				char *arg = strtok(0, DELIMINATORS);
				if(arg) { chdir(arg); }
			}
			// "exit" is also a built-in
			else if(strcmp(cmd, "exit") == 0)
			{
				break;
			}
			else { system(line); }
		}
		fflush(stdout); // Flush after input.

	}
	printf("\n");
	exit(EXIT_SUCCESS);
}
