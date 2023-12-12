#include "shell.h"
/**
 * exec_prompt - Executes a command in a forked child process using execve
 * @stringcommand: The path to the executable file
 */
void exec_promt(const char *stringcommand)
{
	extern char **environ;

	pid_t childprocess = fork();

	if (childprocess == -1)
	{
		perror ("error in fork");
		exit (EXIT_FAILURE);
	}
	else if (childprocess == 0)
	{
		/*Dynamically allocate memory for comargs*/
		char **comargs = malloc(3 * sizeof(char *));
		if (comargs == NULL)
		{
			perror("error in malloc");
			exit(EXIT_FAILURE);
		}
		/*splitting the command line into arguments */

		tokens (stringcommand, comargs);
		/* Handle the "exit" command separately */
		if (strcmp(comargs[0], "exit") == 0)
		{
			forExit(NULL);  /* You might need to pass a par_t structure if needed*/
			free(comargs);  /* Free allocated memory*/
			exit(EXIT_SUCCESS);  /* Make sure to exit the child process*/
		}
		/*handle path */
		handle_path(comargs[0], comargs);
		if (execve(comargs[0], comargs, environ) == -1)
		{
			perror("error in execve");
			free(comargs);
			exit(EXIT_FAILURE);
		}
	}
	else 
	{
		int status;
		waitpid (childprocess, &status, 0);

		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		{
			fprintf(stderr, "%s: Command not found\n", stringcommand);
		}
		else
		{
			perror("Error in child process");
		}
	}
}
