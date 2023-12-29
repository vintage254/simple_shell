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
	char *relative_path = arg[0];
	char *absolute_path = realpath(relative_path, NULL);

	if (absolute_path != NULL)
	{
		free(arg[0]);
		arg[0] = absolute_path;
		return absolute_path;
	}
	else
	{
		if (errno == ENOENT)
		{
			fprintf(stderr, "%s: %d: %s: not found\n", argv, c, temp);
		}
		else
		{
			perror("realpath");
		}
		freeTokens(arg);
		return (NULL);
	}
}
