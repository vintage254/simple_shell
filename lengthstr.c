#include "shell.h"
/**
 * lengthstr - to output the string length
 * @s: the pointer for s
 * Return: 0 success
 */
int lengthstr(const char *s)
{
	int t;
	int scount = 0;

	for (t = 0; s[t] != '\0'; t++)
		scount++;
	return (scount);
}
