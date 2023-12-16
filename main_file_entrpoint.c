#include"shell.h"
int main(int __attribute__((unused)) argh, char *argv[], char *env[])
{
	char *provide = NULL;
	int c = 0;
	int exit_status = 0;
	int struc;

	if (isatty(STDIN_FILENO))
	{
		while (1)
		{
			c++;
			letsprint("cisfun$ ");
			struc = check_char(provide, env, c, argv[0]);
			if (struc != EOF && struc != 7)
				exit_status = struc;
			else if (struc == EOF)
				exit(exit_status);
		}
	}
	else
	{
		while (1)
		{
			c++;
			struc = check_char(provide, env, c, argv[0]);
			if (struc != EOF && struc != 7)
				exit_status = struc;
			else if (struc == EOF)
				exit(exit_status);
		}
	}
	return (exit_status);
}
