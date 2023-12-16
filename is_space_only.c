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
			return (0);  /* Non-space character found*/
		str++;
	}
	return (1);  /* Only spaces found*/
}
/**
 * handle_relative_path - Handles the case when args[0] is a relative path
 * @arg: Array of tokens
 * @temp: Temporary buffer
 * @c: Number of times the shell has run
 * @argv: Name of the shell
 * Return: The exit status
 */
char *handle_relative_path(char **arg, char *temp, int c, char *argv)
{
	char *p = realpath(arg[0], NULL);

	if (p != NULL)
	{
		free(arg[0]);
		arg[0] = p;
	}
	else
	{
		freeTokens(arg);
		fprintf(stderr, "%s: %d: %s: not found\n", argv, c, temp);
	}
	return (p);
}
