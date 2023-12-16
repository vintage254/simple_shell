#include "shell.h"
/**
 * execute_command - functions to execute the command
 * @arg: array of tokens passed
 * @env: environment variable
 * @c: number of times shell has run
 * @argv: shell name
 * Return: exit status of the executed command
 */
int execute_command(char **arg, char *env[], int c, char *argv)
{
	pid_t child_pid = fork();
	int struc, exit_status = 0;
	
	if (getpath(arg, c, argv) == 127)
	{
		/* Handle failure (return 127 or perform appropriate action)*/
		return (127);
	}

	if(child_pid == -1)
	{
		perror("fork");
		return (1);
	}
	else if (child_pid == 0)
	{
		if (execve(arg[0], arg, env) == -1)
		{
			freeTokens(arg);
			perror("execve");
			exit((errno == ENOENT ? 127 : errno));
		}
	}
	else
	{
		waitpid(child_pid, &struc, 0);
		if (WIFEXITED(struc))
			exit_status = WEXITSTATUS(struc);
		else
			exit_status = 1; /* Child process did not exit normally */
		freeTokens(arg);
	}
	return (exit_status);

}
