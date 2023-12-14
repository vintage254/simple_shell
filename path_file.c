#include "shell.h"
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * construct_full_path - construct the full path to the executable.
 * @token: The current token from PATH.
 * @command: The command to be executed.
 * Return: The dynamically allocated full path.
 */
static char *construct_full_path(const char *token, const char *command)
{
	char *full_path = malloc(strlen(token) + strlen(command) + 2);

	if (full_path == NULL)
	{
		perror("error in malloc");
		exit(EXIT_FAILURE);
	}

	strcpy(full_path, token);
	strcat(full_path, "/");
	strcat(full_path, command);

	return (full_path);
}
/**
 * execute_command - Execute the command using execvp.
 * @comargs: An array to store the resulting tokens for execution.
 * @full_path: The full path to the executable.
 */
void execute_command(char **comargs)
{
	if (execvp(comargs[0], comargs) == -1)
	{
		perror("execvp failed");
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
	char *full_path = construct_full_path(token, command);
	struct stat file_stat;

	if (stat(full_path, &file_stat) == 0 &&
		S_ISREG(file_stat.st_mode) &&
		(file_stat.st_mode & S_IXUSR))
	{
		execute_command(comargs);
		free(full_path);
		return (1);
	}

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
	char *path = getenv("PATH");

	/*Check if PATH is not set*/
	if (path == NULL)
	{
		letsprint("problem with the PATH environment .\n");
		exit(EXIT_FAILURE);
	}
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
