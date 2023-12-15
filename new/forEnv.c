#include "shell.h"
#include <unistd.h>

/**
 * forEnv - builtin function to print current env
  */

void forEnv(void)
{
	char **env = environ;

	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}
