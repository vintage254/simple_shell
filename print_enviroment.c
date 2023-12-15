#include "shell.h"
#include <sys/wait.h>
/**
 * env_print - print environment variable
 * @env: environment variables
 */
void env_print(char *env[])
{
	char *list[] = {"/bin/sh", "-c", "env", NULL};

	if (fork() == 0)
	{
		execve(list[0], list, env);
	}
	else
	{
		wait(NULL);
	}

}
