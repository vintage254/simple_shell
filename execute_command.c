#include "shell.h"
/**
 * execute_command - functions to execute the command
 * @arg: array of tokens passed
 * @env: environment variable
 * @count: number of times shell has run
 * @argv: shell name
 * Return: exit status of the executed command
 */

int execute_command(char **arg, char *env[], int count, char *argv)
{
	pid_t child_pid = fork();
	int exit_status = 0;

	if (getpath(arg, count, argv) == 127)
	{
		/* Handle failure (return 127)*/
		return (127);
	}

	if (child_pid == -1)
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
		int status;

		waitpid(child_pid, &status, 0);
		if (WIFEXITED(status))
		{
			exit_status = WEXITSTATUS(status);
		}
		else
		{
			exit_status = 1;
		}
		freeTokens(arg);
	}
	return (exit_status);
}
