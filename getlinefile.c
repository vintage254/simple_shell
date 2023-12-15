#include "shell.h"

/**
 * gline - Custom implementation of getline function
 * @lineptr: Pointer to the buffer storing the input line
 * @n: Pointer to the size of the buffer
 * @stream: Input stream (typically stdin)
 * Return: Number of characters read (including newline), or -1 on failure
 */
ssize_t gline(char **lineptr, size_t *n, FILE *stream)
{
	ssize_t chars_read;
	size_t i = 0;
	int c;
	
	if (lineptr == NULL || n == NULL)
	{
		errno = EINVAL;
		return -1;
	}
	
	/* Allocate initial buffer or resize if necessary*/
	if (*lineptr == NULL || *n == 0)
	{
		*n = 128;  /* Initial buffer size*/
		*lineptr = malloc(*n);
		if (*lineptr == NULL)
		{
			perror("malloc");
			return -1;
		}
	}
	/* Read characters until newline or end of file*/
	while ((c = fgetc(stream)) != EOF && c != '\n')
	{
		/* Resize buffer if needed*/
		if (i >= *n - 1)
		{
			char *new_lineptr;
			*n *= 2;  /* Double the buffer size*/
			*new_lineptr = realloc(*lineptr, *n);
			if (new_lineptr == NULL)
			{
				perror("realloc");
				return -1;
			}
			*lineptr = new_lineptr;
		}
		(*lineptr)[i++] = (char)c;
	}
	/* Null-terminate the string*/
	(*lineptr)[i] = '\0';
	/* Return the number of characters read (including newline)*/
	chars_read = (ssize_t)i + (c == '\n' ? 1 : 0);
	if (c == EOF && i == 0)
		return -1;  /* No characters read*/
	return chars_read;
}

