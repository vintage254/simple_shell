#include "shell.h"
/**
 * exec_prompt - Executes a command in a forked child process using execve
 * @stringcommand: The path to the executable file
 */
void exec_promt(const char *stringcommand)
{
	pid_t childprocess = fork();
	char *envp[] = {NULL};

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
		comargs[0] = (char *)stringcommand;
		comargs[1] = NULL;
		comargs[2] = NULL;

		if (execve (stringcommand,comargs, envp) == -1)
		{
			perror("error in execve");
			free (comargs);
			exit (EXIT_FAILURE);
		}
		free(comargs);/*Free allocated memory after execve (should not reach here)*/
	}
	else 
	{
		wait (NULL);
	}
}
