#include <stdlib.h>
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
		stats = atoi(pars->args[1]);
	}
	
	letsprint("Exiting shell with status ");
	letsprint_int(stats);
	letsprint("\n");

	exit(stats);
}
