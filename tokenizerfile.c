#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "shell.h"

/**
 * no_of_tokens - Helper function to count the number of tokens in a string
 * @input_string: string
 * Return: number of tokens
 */
int no_of_tokens(const char *input_string)
{
	int token_no = 0;
	const char *ptr = input_string;

	while (*ptr)
	{
		while (isspace(*ptr))
			ptr++;
		if (*ptr)
		{
			token_no++;
			while (*ptr && !isspace(*ptr))
				ptr++;
		}
	}

	return (token_no);
}

/**
 * tokenize - an helper function for tokenizing a string
 * @input_string: string input
 * @token_no: the number of tokens
 * Return: an array of tokenized strings
 */
char **tokenize(const char *input_string, int token_no)
{
	const char *ptr = input_string;
	char **tocken;
	size_t t_Length;
	const char *start;
	int index = 0;

	tocken = (char **)malloc((token_no + 1) * sizeof(char *));
	if (!tocken)
	{
		return (NULL);
	}

	ptr = input_string;
	while (*ptr)
	{
		while (isspace(*ptr))
			ptr++;
		if (*ptr)
		{
			start = ptr;
			while (*ptr && !isspace(*ptr))
				ptr++;
			t_Length = ptr - start;

			tocken[index] = (char *)malloc((t_Length + 1) * sizeof(char));
			if (!tocken[index])
			{
				freeTokens(tocken);
				return (NULL);
			}

			strncpy(tocken[index], start, t_Length);
			tocken[index++][t_Length] = '\0';
		}
	}

	tocken[index] = NULL;
	return (tocken);
}

/**
 * tokenizermspace - Function to tokenize a string and
 * remove spaces, tabs, and newlines
 * @input_string: string
 * Return: array of tokenized strings
 */
char **tokenizermspace(char *input_string)
{
	int token_no = no_of_tokens(input_string);
	char **tocken;

	if (token_no == 0)
	{
		free(input_string);
		return (NULL);
	}

	tocken = tokenize(input_string, token_no);

	free(input_string);
	return (tocken);
}

/**
 * freeTokens - Function to free the memory allocated for tokens
 * @tocken: array of string tokens
 */
void freeTokens(char **tocken)
{
	int i;

	for (i = 0; tocken[i]; i++)
		free(tocken[i]);
	free(tocken);
}
