#include "shell.h"
/**
 * tockens - Tokenizes a command line string into an array of strings.
 * @commandline: The command line string to be tokenized.
 * @args: The array to store the resulting tokens.
 */
void tokens(const char *commandline, char **args)
{
	char *token;
	int i = 0;

	token = strtok((char *)commandline, " ");
	while (token != NULL)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;
}
