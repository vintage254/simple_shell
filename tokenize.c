#include "shell.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * token_s - for tockenizing the strings
 * @string: string to tokenize
 * @delmtr: the string to be used as a delimeter
 * Return: pointer to token
 */
char *token_s(char *string, char *delmtr)
{
	static char *_string;
	char *tocken = NULL;
	char *_delmtr = NULL;

	if (string != NULL)
		_string = string;

	if (_string == NULL)
		return (NULL);

	tocken = _string;
	_delmtr = token_s(_string, delmtr);

	if (_delmtr != NULL)
	{
		*_delmtr = '\0';
		_string = _delmtr + 1;
	}
	else
	{
		_string = NULL;
	}

	return (tocken);
}
