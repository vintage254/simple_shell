#include "shell.h"
#include <string.h>
/**
 * stringcopy - copies a string from one place to another
 * @destination: pointer
 * @strc: pointer
 * Return: the copied string
 */
char *stringcopy(char *destination, char *strc)
{
	int i;

	for (i = 0; strc[i] != '\0'; i++)
	{
		destination[i] = strc[i];
	}
	destination[i] = '\0';
	return (destination);
}
