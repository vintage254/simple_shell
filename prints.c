#include "shell.h"
/**
 * letsprint - the printing function
 * @displaying: the displaying terminal
*/
void letsprint(const char *displaying)
{
	write(1, displaying, _strlen(displaying));
}
