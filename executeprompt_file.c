#include "shell.h"
#include <stdlib.h>
#include <unistd.h>
/**
 * exec_prompt - Executes a command in a forked child process using execve
 * @stringcommand: The path to the executable file
 */
void exec_promt(const char *stringcommand)
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
 * exec_child - Function to execute child process using execve
 * @stringcommand: The path to the executable file
 */
void exec_child(const char *stringcommand)
{
	/*Dynamically allocate memory for comargs*/
	char *comargs[2];
	comargs[0] = (char *)stringcommand;
	comargs[1] = NULL;

	/* Handle the "exit" command separately */
	if (strcmp(comargs[0], "exit") == 0)
	{
		forExit(NULL);
		exit(EXIT_SUCCESS);
	}
	/*handle path */
	handle_path(comargs[0], comargs);

	if (execve(comargs[0], comargs, environ) == -1)
	{
		perror("error in child process execve");
		exit(EXIT_FAILURE);
	}
}

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
