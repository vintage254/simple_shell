#include "shell.h"
/**
 * letsprint - Prints the given command line to standard output
 * @commandline: A pointer to a constant string representing the command line
 */
void letsprint (const char *commandline)
{
	if (write(STDOUT_FILENO, commandline, strlen(commandline)) == -1)
	{
		perror ("error");
		exit(EXIT_FAILURE);
	}
}
