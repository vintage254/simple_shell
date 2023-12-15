#include "shell.h"
void execute_command(const char *command)
{
	pid_t child_pid = fork();

	if(child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (child_pid == 0)
	{
		char *args[2];
		args[0] = (char *)command;
		args[1] = NULL;
		
		if (execve(command, args, NULL) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(NULL);
	}
}
