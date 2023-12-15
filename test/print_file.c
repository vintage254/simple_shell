#include "shell.h"
void letsprint(const char *message)
{
	write(STDOUT_FILENO, message, strlen(message));
}
