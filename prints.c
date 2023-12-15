#include "shell.h"
/**
 * letsprint - the printing function
 * @displaying: the displaying terminal
*/
void letsprint(char *displaying)
{
	write(1, displaying, _strlen(displaying));
}
