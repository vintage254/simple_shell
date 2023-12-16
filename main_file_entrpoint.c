#include"shell.h"
/**
 * main - Entry point of the shell program
 * @argh: The number of command-line arguments (unused).
 * @argv: An array of strings containing the command-line arguments.
 * @env: An array of strings containing the environment variables.
 *
 * Return: 0 on successful execution of the shell program.
 */
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
			struc = char_check(provide, env, c, argv[0]);
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
			struc = char_check(provide, env, c, argv[0]);
			if (struc != EOF && struc != 7)
				exit_status = struc;
			else if (struc == EOF)
				exit(exit_status);
		}
	}
	return (exit_status);
}
