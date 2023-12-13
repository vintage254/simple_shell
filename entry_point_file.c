#include "shell.h"

/**
 * main - Entry point of the shell program
 *
 * Return: Always 0 (success)
 */
int main(void)
{
	char *input_buffer = NULL;
	size_t buffer_size = 0;
	ssize_t chars_read;

	while (1)
	{
		printf("#cisfun$ ");
		chars_read = getline_func(input_buffer, buffer_size);

		if (chars_read == -1)
		{
			/* End of file reached (Ctrl+D), exit the shell*/
			printf("\n");
			break;
		}

		input_buffer[strcspn(input_buffer, "\n")] = ('\0');

		exec_promt(input_buffer);
	}

	free(input_buffer);
	return (0);
}
