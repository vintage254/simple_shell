#include "shell.h"
void read_command(char *command, size_t size)
{
	if (fgets(command, size, stdin) == NULL)
	{if (feof (stdin))
		{
			letsprint("\n");
			exit (EXIT_SUCCESS);
		}
		else
		{
			letsprint("error while reading input,\n");
			exit (EXIT_FAILURE);
		}
	}
	command[strcspn(command,"\n")] = '\0';
}
