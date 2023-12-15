#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * setEnv - Initialize a new environment variable or modify an existing one.
 * @pars: Parameters including the command line arguments.
 */
/*void setEnv(par_t *pars)
{
	if (pars->args[1] && pars->args[2])
	{
		if (setenv(pars->args[1], pars->args[2], 1) != 0)
		{
			perror("setenv");
		}
	}
	else
	{
		fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
	}
}*/

/**
 * unsetEnv - Remove an environment variable.
 * @pars: Parameters including the command line arguments.
 */
/*void unsetEnv(par_t *pars)
{
	if (pars->args[1])
	{
		if (unsetenv(pars->args[1]) != 0)
		{
			perror("unsetenv");
		}
	}
	else
	{
		fprintf(stderr, "Usage: unsetenv VARIABLE\n");
	}
}*/

/**
 * cd - Changes the current directory of the process.
 * @pars: Parameters including the command line arguments.
 */
/*void cd(par_t *pars)
{
	if (pars->args[1])
	{
		if (chdir(pars->args[1]) != 0)
		{
			perror("cd");
		}
		else
		{
			setenv("PWD", pars->args[1], 1);
		}
	}
	else
	{
		/* If no argument is given, change to the home directory */
		char *home = getenv("HOME");

		if (home)
		{
			if (chdir(home) != 0)
			{
				perror("cd");
			}
			else
			{
				setenv("PWD", home, 1);
			}
		}
	}
}*/
