#include <stdlib.h>
#include <limits.h>
#include "shell.h"

/**
 * forExit - buildin exit function
 * @pars: parameters
 */
void forExit(par_t *pars)
{
	int stats = 0;

	if (!pars->args[1])
	{
		stats = pars->stats;
		exit(stats);
	}
}
