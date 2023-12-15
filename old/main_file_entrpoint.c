#include"shell.h"
int main(void)
{
	char command [300];
	while (1)
	{
		cshell();
		read_command(command, sizeof(command));
		execute_command(command);
	}
	return 0;
}
