#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "shell.h"

/**
 * forExit - buildin exit function
 */
void forExit(void)
{
	fprintf(stdout, "Exiting shell with status %d\n", EXIT_SUCCESS);
	exit(EXIT_SUCCESS);
}
