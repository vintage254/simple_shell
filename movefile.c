#include "shell.h"
/**
 * move - copy source to destination
 * @buffer: destination buffer
 * @source: source buffer
 */
void move(char *destination, char *source)
{
	char *tmp;

	tmp = destination;
	while (*source != '#' && *source)
	{
		*tmp = *source;
		source++;
		tmp++;
	}
	/*terminate tmp*/
	*tmp = '\0';
}
