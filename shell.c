//
// Created by abdullah on 4/17/16.
//

#include "shell.h"

// List of builtin commands
char * builtins[] = { "cd", "exit" };
// Call builtin function.
int (*builtin_function[]) (char**) = { &sh_cd, &sh_exit };
// Return number of builtins
int num_builtins()
{
    return sizeof(builtins) / sizeof(char *);
}

// The print_color functions print text in their respective colors.
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

// Prints user@host prompt.
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

// Our shell main loop
void sh_loop(void)
{
    char * line;
    char ** args;
    int status;

    do
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
        char * home_dir = p->pw_dir;
		/* Print prompt in the format:
		 * [username@hostname current_working_directory] %
		 */
		print_userhost(username, hostname, current_dir);
        line = sh_get_cmd();
        args = sh_tokenize_cmd(line);
        status = sh_launch(args);

        // Free the memory we used.
        free(line);
        free(args);
    } while(status);
}

// Implement sh_get_cmd
/*
Problem: I don't know how much text a user will enter.
Strategy: Use getline from stdio.h to allocate the proper
amount for me.
*/
char * sh_get_cmd(void)
{
    char * line = NULL;
    ssize_t bufsize = 0; // getline will change this.
    // Get the line from user input.
    getline(&line, &bufsize, stdin);
    return line;
}

char ** sh_tokenize_cmd(char * cmd)
{
    int bufsize = TOKEN_BUFSIZE;
    int pos = 0;
    char ** tokens = malloc(bufsize * sizeof(char*));
    char * token;

    // Check for allocation error.
    if(!tokens)
    {
        fprintf(stderr, "Allocation error.\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(cmd, TOKEN_DELIMS);
    while(token != NULL)
    {
        tokens[pos] = token;
        pos++;

        // Reallocate if tokens don't fit.
        if(pos >= bufsize)
        {
            bufsize += TOKEN_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char*));

            // Check for allocation error.
            if(!tokens)
            {
                fprintf(stderr, "Allocation error.\n");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, TOKEN_DELIMS);
    }
    tokens[pos] = NULL;
    return tokens;
}

// Finally, launching a program.
int sh_launch(char ** args)
{
    pid_t pid, wpid;
    int status;

    pid = fork();
    if(pid == 0) // Child process.
    {
        if(execvp(args[0], args) == -1)
        {
            perror("yash");
        }
        exit(EXIT_FAILURE);
    }
    else if (pid < 0) // fork() error
    {
        perror("fork()");
    }
    else // Parent process.
    {
        do
        {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while(!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}

// Builtins
int sh_cd(char ** args)
{
    // cd without parameters should take you to home_dir.
    if(args[1] == NULL)
    {
        fprintf(stderr, "Expected argument for \"cd\".\n");
    }
    else
    {
        if(chdir(args[1]) != 0) { perror("cd error"); }
    }
    return 1;
}

int sh_exit(char ** args)
{
    return 0;
}

int sh_execute(char ** args)
{
    int idx;
    if(args[0] == NULL) // Empty command.
    {
        return 1;
    }

    for(idx = 0; idx < num_builtins(); idx++)
    {
        if(strcmp(args[0], builtins[idx]) == 0)
        {
            return (*builtin_function[idx])(args);
        }
    }

    return sh_launch(args);
}
