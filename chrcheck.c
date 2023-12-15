#include "shell.h"
#include <signal.h>
/**
 * termi_null - to null terminate a string
 * @input_string: input string from getlin
 * Return: null terminated string
*/
char *termi_null(char *input_string)
{
	int t;

	for (t = 0; input_string[t] != '\0'; t++)
	{
		if (input_string[t] == '\n')
			input_string[t] = '\0';
	}
	return (input_string);
}

/**
 * char_check - checking characters in the commamnd
 * @input_string: character to check
 * @env: the environment variable
 * @argh: the name of the shell
 * @c: the no of times shell has run
 * Return: exit status of the executed command
 */
int char_check(char *input_string, char *env[], int c, char *argh)
{
	ssize_t c_chars;
	int exit_s = 0;
	size_t sizes = 0;
	char **arg = NULL;

	c_chars = getline(&input_string, &sizes, stdin);
	if (c_chars == -1)
	{
		free(input_string);
		if (isatty(STDIN_FILENO))
			write(1, "\n", 1);
		return (-1);
	}

	termi_null(input_string);
	arg = tokenizermspace(input_string);

	if (arg == NULL)
		return (5);

	if (stringcmp(arg[0], "quit") == 0)
	{
		freeTokens(arg);
		return (-1);
	}

	else if (stringcmp(arg[0], "environment") == 0)
	{
		freeTokens(arg);
		env_print(env);
	}

	else
		exit_s = execute_command(arg, env, c, argh);

	return (exit_s);
}
