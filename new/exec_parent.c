#include "shell.h"
/**
 * exec_parent - Waits for the child process to complete, handles the status
 * @childprocess: The process ID of the child process.
 */
void exec_parent(pid_t childprocess)
{
	int status;

	if (waitpid(childprocess, &status, 0) == -1)
	{
		perror("Error waiting for child process");
		return;
	}

	if (WIFEXITED(status))
	{
		int exit_status = WEXITSTATUS(status);

		if (exit_status != 0)
		{
			fprintf(stderr, "non-zero exit: %d\n", exit_status);
		}
	}
	else if (WIFSIGNALED(status))
	{
		fprintf(stderr, "termntd by signal: %d\n", WTERMSIG(status));
	}
	else
	{
		fprintf(stderr, "Child process did not terminate normally\n");
	}
}
/**
 * create_full_path - Creates a full path combing a directory and a command.
 * @directory: The directory where the command is located.
 * @command: The command to be executed.
 *
 * Return: full path on success, NULL on failure
 */
char *create_full_path(const char *directory, const char *command)
{
	size_t len = strlen(directory) + 1 + strlen(command) + 1;
	char *full_path = malloc(len);

	if (full_path == NULL)
	{
		perror("Error allocating memory");
		exit(EXIT_FAILURE);
	}

	snprintf(full_path, len, "%s/%s", directory, command);

	return (full_path);
}
