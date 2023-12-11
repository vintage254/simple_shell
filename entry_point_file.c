#include "shell.h"

/**
 * main - Entry point of the shell program
 *
 * Return: Always 0 (success)
 */
int main(void)
{
	char comm[300];
	ssize_t chars_read;

	while (1)
	{
		allsmiles();
		chars_read = getline_func(comm, sizeof(comm));
		if (chars_read == -1)
		{
			/* End of file reached (Ctrl+D), exit the shell*/
			exit(EXIT_SUCCESS);
		}
		read_user_input(comm, sizeof(comm));
		exec_promt(comm);
	}
	return (0);
}
