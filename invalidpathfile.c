#include "shell.h"
/**
 * invalidpath - check if path is valid
 * @arg: array of tokens
 * Return: 127 (invalid) / 0 (valid)
*/
int invalidpath(char **args)
{
	if (access(arg[0], X_OK) != 0)
		return (127);
	return (0);
}
