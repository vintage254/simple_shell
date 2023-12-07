#include "shell.h"

/**
 * main - Entry point of the shell program
 *
 * Return: Always 0 (success)
 */
int main(void)
{
	char comm[300];

	while (1)
	{
		allsmiles();
		read_user_input(comm, sizeof(comm));
		exec_promt(comm);
	}
	return (0);
}
