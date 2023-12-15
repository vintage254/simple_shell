#include "shell.h"

/**
 * prompt - Execute the user input.
 *
 * @input: User input.
 * @pars: Pointer to the par_t structure.
 * @full_path: The full path to executable
 * Return: 0 on success, -1 on failure.
 */
int prompt(char *input, par_t *pars, const char *full_path)
{
	pid_t pid;
        int status;

	if (input == NULL || pars == NULL || full_path == NULL)
		return (-1);

	tokens(input, &(pars->argv));

	pid = fork();
	if (pid == 0)
	{
		if (execve(full_path, pars->argv, environ) == -1)
		{
			perror(input);
			fprintf(stderr, "Error executing command: %s\n", full_path);
			_exit(EXIT_FAILURE);
		}

		handle_path(pars->argv[0], pars->argv);
		execute_command(pars->argv);
	}
	else if(pid < 0)
	{
		perror("Fork failed");
		free_tokens(pars->argv);
		return (-1);
	}
	else
	{
		waitpid(pid, &status, 0);
	}

	free_tokens(pars->argv);

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
	char *full_path;

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
		fgets(input_buffer, BUFFER_SIZE, stdin);

		if (input_buffer == NULL || feof(stdin))
		{
			/* End of file reached (Ctrl+D), exit the shell*/
			letsprint("\n");
			break;
		}

		input_buffer[strcspn(input_buffer, "\n")] = '\0';

		full_path = construct_full_path("/bin", input_buffer);

		if (full_path == NULL)
		{
			letsprint("Error creating full path.\n");
			free(input_buffer);
			continue;
		}

		if (prompt(input_buffer, &pars, full_path) == -1)
		{
			letsprint("Error executing command.\n");
		}

		free(input_buffer);
		free(full_path);
	}
	return (0);
}
