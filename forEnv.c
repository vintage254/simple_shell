#include "shell.h"
/**
 * forEnv - builtin function to print current env
 * @environ: current environment
  */

void forEnv(void)
{
	extern char **environ;
	char **env = environ;
	
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}
