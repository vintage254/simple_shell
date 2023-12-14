#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
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

	/* Handle the "exit" command separately */
	if (strcmp(comargs[0], "exit") == 0)
	{
		forExit(pars);
		exit(EXIT_SUCCESS);
	}
	/* Handle the "setenv" command */
	else if (strcmp(comargs[0], "setenv") == 0)
	{
		setEnv(pars);
		exit(EXIT_SUCCESS);
	}
	/* Handle the "unsetenv" command */
	else if (strcmp(comargs[0], "unsetenv") == 0)
	{
		unsetEnv(pars);
		exit(EXIT_SUCCESS);
	}
	/* Handle the "cd" command */
	else if (strcmp(comargs[0], "cd") == 0)
	{
		cd(pars);
		exit(EXIT_SUCCESS);
	}
	/*handle path */
	handle_path(comargs[0], comargs);

	free(comargs[0]);

	if (execve(comargs[0], comargs, environ) == -1)
	{
		perror("error in child process execve");
		exit(EXIT_FAILURE);
	}
}
/**
 * exec_parent - Waits for the child process to complete, handles the status.
 * @childprocess: The process ID of the child process.
 *
 * This function waits for the child process specified by 'childprocess' to
 * complete its execution. It then examines the status of the child process and
 * prints an error message if the child process did not exit successfully.
 *
 * @childprocess: The process ID of the child process to wait for.
 */
void exec_parent(pid_t childprocess)
{
	int status;

	waitpid(childprocess, &status, 0);

	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		fprintf(stderr, "Command not found\n");
	}
	else
	{
		perror("Error in child process");
	}
}
