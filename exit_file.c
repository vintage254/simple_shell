#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "shell.h"

/**
 * forExit - buildin exit function
 * @pars: parameters
 */
void forExit(par_t *pars)
{
	int stats = EXIT_SUCCESS;

	if (pars->args[1] != NULL)
	{
		char *endptr;
		long temp_stats = strtol(pars->args[1], &endptr, 10);

		if (*endptr == '\0' &&
			temp_stats >= INT_MIN &&
			temp_stats <= INT_MAX)
		{
			stats = (int)temp_stats;
		}
		else
		{
			fprintf(stderr, "Error exit: %s\n", pars->args[1]);
			return;
		}
	}

	fprintf(stdout, "Exiting shell with status %d\n", stats);
	exit(stats);
}
