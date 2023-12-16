#include "shell.h"
#include <unistd.h>
/**
 * letsprint - the printing function
 * @displaying: the displaying terminal
*/
void letsprint(const char *displaying)
{
	write(1, displaying, lengthstr(command));
}
