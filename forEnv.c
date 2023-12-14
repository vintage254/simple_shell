#include "shell.h"
/**
 * forEnv - builtin function to print current env
  */

void forEnv(void)
{
	char **environ;
	char **env = environ;

	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}
