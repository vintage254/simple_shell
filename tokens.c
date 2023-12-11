#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

/**
 * tokens_ - Tokenizes a command line string into an array of strings.
 * @commandline: The command line string to be tokenized.
 * @args: The array to store the resulting tokens.
 */
void tokens_(const char *commandline, char **args)
{
	int i = 0;
	int arg_index = 0;
	int in_word = 0; /*flag to show we are inside a word*/

	while (commandline[i] != '\0')
	{
		if (commandline[i] == ' ' || commandline[i] == '\t' ||
			commandline[i] == '\n')
		{
			if (in_word)
			{
				args[arg_index++] = NULL;
				in_word = 0; /*reset flag*/
			}
		}
		else
		{
			if (!in_word)
			{
				args[arg_index] = (char *)&commandline[i];
				in_word = 1;
			}
		}

		i++;
	}

	if (in_word)
		args[arg_index++] = NULL;
	args[arg_index] = NULL;
}
