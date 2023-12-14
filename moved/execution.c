#include "shell.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
/**
 * exec_prompt - Executes a command in a forked child process using execve.
 * @stringcommand: The path to the executable file.
 * @pars: Parameters including the command line arguments.
 */
void exec_prompt(const char *stringcommand, par_t *pars)
{
	pid_t childprocess = fork();

	if (childprocess == -1)
	{
		perror("error in fork");
		exit(EXIT_FAILURE);
	}
	else if (childprocess == 0)
	{
		exec_child(stringcommand, pars);
	}
	else
	{
		exec_parent(childprocess);
	}
}
/**
 * exec_child - Function to execute child process using execve.
 * @stringcommand: The path to the executable file.
 * @pars: Parameters including the command line arguments.
 */
void exec_child(const char *stringcommand, par_t *pars)
{
    /*Dynamically allocate memory for comargs*/
	char *comargs[2];

	comargs[0] = strdup(stringcommand);
	comargs[1] = NULL;

	fprintf(stderr, "Executing command: %s\n", comargs[0]);

	/* Handle the "exit" command separately */
	if (handle_builtin_commands(comargs, pars) == 1)
	{
		free(comargs[0]);
		exit(EXIT_SUCCESS);
	}

	fprintf(stderr, "Calling handle_path_and_execute\n");

	handle_path_and_execute(comargs);

	free(comargs[0]);
}

/**
 * handle_builtin_commands - Handles built-in command
 *
 * @command: The command to be executed.
 * @pars: Parameters including the command line arguments.
 *
 * Return: 0 on success, -1 on failure.
 */
int handle_builtin_commands(char **command, par_t *pars)
{
	if (strcmp(command[0], "exit") == 0)
	{
		forExit(pars);
	}
	/* Handle the "setenv" command */
	else if (strcmp(command[0], "setenv") == 0)
	{
		setEnv(pars);
	}
	/* Handle the "unsetenv" command */
	else if (strcmp(command[0], "unsetenv") == 0)
	{
		unsetEnv(pars);
	}
	/* Handle the "cd" command */
	else if (strcmp(command[0], "cd") == 0)
	{
		cd(pars);
	}
	else
	{
		execute_command(command);
	}
	return (0);
}
/**
 * handle_path_and_execute - Handles path and executes command using execve
 *
 * @comargs: An array containing the command and its arguments.
 */
void handle_path_and_execute(char *comargs[2])
{
	char *path_copy, *token;
	char *path = getenv("PATH");

	if (strchr(comargs[0], '/') != NULL)
	{
		if (execve(comargs[0], comargs, environ) == -1)
		{
			perror("execve failed");
			free(comargs[0]);
			exit(EXIT_FAILURE);
		}
	}
	if (path == NULL)
	{
		fprintf(stderr, "PATH environment variable is not set\n");
		exit(EXIT_FAILURE);
	}

	path_copy = strdup(path);
	if (path_copy == NULL)
	{
		perror("Error duplicating PATH");
		exit(EXIT_FAILURE);
	}

	token = strtok(path_copy, ":");
	while (token != NULL)
	{
		char *full_path = create_full_path(token, comargs[0]);
		if (full_path != NULL)
		{
			fprintf(stderr, "Attempting execute: %s\n", full_path);
			if (execve(full_path, comargs, environ) != -1)
			{
				fprintf(stderr, "Success: %s\n", full_path);
				free(full_path);
				free(path_copy);
				exit(EXIT_SUCCESS);
			}
			else
			{
				if (errno == ENOENT)
				{
					fprintf(stderr, "c: %s\n", comargs[0]);
					free(full_path);
					free(path_copy);
					exit(EXIT_FAILURE);
				}
				else
				{
					fprintf(stderr, "Execution failed for %s: %s\n", full_path, strerror(errno));
					free(full_path);
				}
			}
		}

		token = strtok(NULL, ":");
	}

	fprintf(stderr, "No valid path found for command: %s\n", comargs[0]);
	free(path_copy);
	exit(EXIT_FAILURE);
}
