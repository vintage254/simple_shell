#include "shell.h"
void execute_command(char **arg, char *env[], int count, char *argv)
{
	pid_t child_pid = fork();
	int sruct, exit_status = 0;
	
	if (getpath(arg, count, argv) == 127)
	{
		/* Handle failure (return 127 or perform appropriate action)*/
		return (127);
	}

	if(child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (child_pid == 0)
	{
		if (execve(command, arg, NULL) == -1)
		{
			freeTokens(arg);
			perror("execve");
			exit((errno == ENOENT ? 127 : errno));
		}
	}
	else
	{
		else
		{
			waitpid(child_pid, &status, 0);
			if (WIFEXITED(status))
				exit_status = WEXITSTATUS(status);
			else
				exit_status = 1; /* Child process did not exit normally */
			freeTokens(arg);
		}
	}
}
