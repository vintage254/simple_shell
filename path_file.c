#include "shell.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * construct_full_path - construct the full path to the executable.
 * @token: The current token from PATH.
 * @command: The command to be executed.
 * Return: The dynamically allocated full path.
 */
char *construct_full_path(const char *token, const char *command)
{
	size_t token_len = strlen(token);
	size_t command_len = strlen(command);
	size_t full_path_size = token_len + command_len + 2;

	char *full_path = malloc(full_path_size);

	if (full_path == NULL)
	{
		perror("error in malloc");
		exit(EXIT_FAILURE);
	}

	if (full_path_size <= token_len + 1 || full_path_size <= command_len + 1)
	{
		perror("insufficient space for full path");
		exit(EXIT_FAILURE);
	}

	strcpy(full_path, token);
	strcat(full_path, "/");
	strcat(full_path, command);

	printf("Constructed full path: %s\n", full_path);

	return (full_path);
}
/**
 * execute_command - Execute the command using execvp.
 * @comargs: An array to store the resulting tokens for execution.
 */
void execute_command(char **comargs)
{
	char **env = environ;

	printf("Executing command: %s\n", comargs[0]);

	while (*env)
	{
		printf("Env: %s\n", *env);
		env++;
	}

	if (execvp(comargs[0], comargs) == -1)
	{
		perror("execvp failed");
		fprintf(stderr, "Error code: %d\n", errno);
		exit(EXIT_FAILURE);
	}

	perror("execvp failed");
	exit(EXIT_FAILURE);
}
/**
 * search_in_path - Search for the executable in a specific PATH directory.
 * @token: The current token from PATH.
 * @command: The command to be executed.
 * @comargs: An array to store the resulting tokens for execution.
 * Return: 1 if the command was found and executed, 0 otherwise.
 */
static int search_in_path(const char *token,
	       const char *command,
	       char **comargs)
{
	char *full_path;
	struct stat file_stat;

	printf("Search path: %s\n", token);
	full_path = construct_full_path(token, command);
	printf("Full path: %s\n", full_path);

	if (stat(full_path, &file_stat) == 0 &&
		S_ISREG(file_stat.st_mode) &&
		(file_stat.st_mode & S_IXUSR))
	{
		printf("Executable found and is executable\n");
		execute_command(comargs);
		free(full_path);
		return (1);
	}

	printf("Executable not found or not executable\n");
	free(full_path);
	return (0);
}

/**
 * handle_path - Search for the executable in directories specified by PATH.
 * @command: The command to be executed.
 * @comargs: An array to store the resulting tokens for execution.
 */
void handle_path(const char *command, char **comargs)
{
	char new_path[1024];
	char *path = getenv("PATH");

	printf("PATH: %s\n", path);

	/*Check if PATH is not set*/
	if (path == NULL)
	{
		letsprint("problem with the PATH environment .\n");
		exit(EXIT_FAILURE);
	}

	snprintf(new_path, sizeof(new_path), "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:%s", path);
	setenv("PATH", new_path, 1);
	/* Check if the command contains a '/'*/

	if (strchr(command, '/') != NULL)
	{
		/* Command contains a '/', execute it directly*/
		comargs[0] = strdup(command);
		if (comargs[0] == NULL)
		{
			perror("error while duplicating");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Command does not contain a '/', search for it in the PATH*/
		char *token = strtok(path, ":");

		while (token != NULL)
		{
			if (search_in_path(token, command, comargs))
				return;

			token = strtok(NULL, ":");
		}

		letsprint("Command not found in PATH: ");
		letsprint(command);
		letsprint("\n");
		exit(EXIT_FAILURE);
		
	}
	/* Set the rest of the arguments to NULL*/
	comargs[1] = NULL;
}
