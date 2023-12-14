#include "shell.h"

/**
 * main - Entry point of the shell program
 *
 * Return: Always 0 (success)
 */
int main(void)
{
	char *input_buffer = NULL;
	ssize_t chars_read;

	par_t pars;

	pars.argv = (NULL);

	while (1)
	{
		letsprint("#cisfun$ ");
		input_buffer = (char *)malloc(BUFFER_SIZE);

		if (input_buffer == NULL)
		{
			perror("Error in malloc");
			exit(EXIT_FAILURE);
		}
		chars_read = getline_func(input_buffer, BUFFER_SIZE);

		if (chars_read == -1)
		{
			/* End of file reached (Ctrl+D), exit the shell*/
			letsprint("\n");
			break;
		}
		input_buffer[strcspn(input_buffer, "\n")] = ('\0');

		exec_prompt(input_buffer, &pars);

		free(input_buffer);
	}
	return (0);
}
