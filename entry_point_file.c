#include "shell.h"
/**
 * prompt - Execute the user input.
 *
 * @input: User input.
 * @pars: Pointer to the par_t structure.
 *
 * Return: 0 on success, -1 on failure.
 */
int prompt(char *input, par_t *pars)
{
	pid_t pid;
	int status;
	char *full_path;

	full_path = input;

	pid = fork();
	if (pid == 0)
	{
		if (execve(full_path, pars->argv, environ) == -1)
		{
			perror(input);
			fprintf(stderr, "Error executing command: %s\n", full_path);
			_exit(EXIT_FAILURE);
		}
	}
	else if(pid < 0)
	{
		perror("Fork failed");
		return (-1);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
	return (0);
}

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
	pars.argv = NULL;

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
		input_buffer[strcspn(input_buffer, "\n")] = '\0';

		exec_prompt(input_buffer, &pars);

		free(input_buffer);
	}
	return (0);
}
