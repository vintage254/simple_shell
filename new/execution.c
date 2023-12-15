#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
/**
 * exec_prompt - Executes a command in a forked child process using execve.
 * @stringcommand: The path to the executable file.
 */
void exec_prompt(const char *stringcommand)
{
	pid_t childprocess = fork();

	if (childprocess == -1)
	{
		perror("error in fork");
		exit(EXIT_FAILURE);
	}
	else if (childprocess == 0)
	{
		exec_child(stringcommand);
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
void exec_child(const char *stringcommand)
{
    /*Dynamically allocate memory for comargs*/
	char *comargs[2];

	comargs[0] = strdup(stringcommand);
	comargs[1] = NULL;

	/* Handle the "exit" command separately */
	if (handle_builtin_commands(comargs) == 1)
	{
		free(comargs[0]);
		exit(EXIT_SUCCESS);
	}

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
int handle_builtin_commands(char **command)
{
	if (strcmp(command[0], "exit") == 0)
	{
		forExit();
	}
	/* Handle the "env" command */
	else if (strcmp(command[0], "env") == 0)
	{
		forEnv();
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
void handle_path_and_execute(char **comargs)
{
	/*handle path */
	handle_path(comargs[0], comargs);

	if (execve(comargs[0], comargs, environ) == -1)
	{
		perror("execve failed");
		fprintf(stderr, "Error executing command: %s\n", comargs[0]);
		free(comargs[0]);
		exit(EXIT_FAILURE);
	}
}
