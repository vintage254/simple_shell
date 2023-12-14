#include "shell.h"
/**
 * exec_parent - Waits for the child process to complete, handles the status
 * @childprocess: The process ID of the child process.
 */
void exec_parent(pid_t childprocess)
{
	int status;

	waitpid(childprocess, &status, 0);

	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		fprintf(stderr, "Command not found\n");
	}
	else
	{
		perror("Error in child process");
	}
}
