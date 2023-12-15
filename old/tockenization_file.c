#include "shell.h"
#include <string.h>
#include <stdlib.h>

/**
 * tokens - Tokenizes a command line string into an array of strings.
 * @commandline: The command line string to be tokenized.
 * @args: The array to store the resulting tokens.
 */
void tokens(const char *commandline, char ***args)
{
	const char *delimiter = " \t\r\n\a";
	char *token = strtok((char *)commandline, delimiter);
	int i = 0;

	*args = (char **)malloc(sizeof(char *));

	while (token != NULL)
	{
		(*args)[i] = (char *)malloc(strlen(token) + 1);
		
		strcpy((*args)[i], token);

		i++;

		*args = (char **)realloc(*args, (i + 1) * sizeof(char *));

		token = strtok(NULL, delimiter);
	}

	(*args)[i] = NULL;
}
/**
 * free_tokens - Frees the memory allocated for an array of tokens.
 * @args: The array of tokens.
 */
void free_tokens(char **args)
{
	int i = 0;

	while (args[i] != NULL)
	{
		free(args[i]);
		i++;
	}

	free(args);
}
