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
/**
 * letsprint_int - Prints an integer to standard output
 * @num: The integer to be printed
 */
void letsprint_int(int num)
{
	char buffer[20];  /* Adjust the size as needed*/
	int len = snprintf(buffer, sizeof(buffer), "%d", num);
	
	if (len < 0 || (size_t)len >= sizeof(buffer))
	{
		/* Handle error*/
		perror("error in letsprint_int");
		exit(EXIT_FAILURE);
	}
	if (write(STDOUT_FILENO, buffer,(size_t)len) == -1)
	{
		perror("error");
		exit(EXIT_FAILURE);
	}
}
