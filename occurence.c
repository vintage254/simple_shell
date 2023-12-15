/**
 * strngocc - find the first occurence of a character in a string
 * @string: the string to search
 * @checkchar: a string of characters to check for
 * Return: pointer to first occurence
 */
#include <stdio.h>

char *strngocc(const char *string, const char *checkchar)
{
	if (string == NULL || checkchar == NULL)
		return (NULL);

	while (*string != '\0')
	{
		const char *curr_char = checkchar;

		while (*curr_char != '\0')
		{
			if (*str == *curr_char)
				return ((char *)string);
			curr_char++;
		}
		string++;
	}
	return (NULL);
}
