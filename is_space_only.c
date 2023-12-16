#include "shell.h"

/**
 * is_spaces_only - Check if a string contains only spaces
 * @str: The input string to check
 * Return: 1 if only spaces, 0 otherwise
 */
int is_spaces_only(const char *str)
{
	while (*str != '\0')
	{
		if (!isspace(*str))
			return 0;  /* Non-space character found*/
		str++;
	}
	return 1;  /* Only spaces found*/
}

