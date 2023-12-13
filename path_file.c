#include "shell.h"
/**
 * handle_path - Search for the executable in directories specified by PATH
 * @command: The command to be executed
 * @comargs: An array to store the resulting tokens for execution
 */
void handle_path(const char *command, char **comargs)
{
	/* Get the PATH environment variable*/
	char *path = getenv("PATH");
	
	/*Check if PATH is not set*/
	if (path == NULL) {
		letsprint("problem with the PATH environment .\n");
		exit(EXIT_FAILURE);
	}
	/* Check if the command contains a '/'*/
	
	if (strchr(command, '/') != NULL)
	{
		/* Command contains a '/', execute it directly*/
		comargs[0] = strdup(command);
		if (comargs[0] == NULL)
		{
			perror("error while duplicating");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Command does not contain a '/', search for it in the PATH*/
		char *token = strtok(path, ":");
		while (token != NULL) {
            /* Construct the full path to the executable*/
			char *full_path = malloc(strlen(token) + strlen(command) + 2);
			if (full_path == NULL)
			{
				perror("error in malloc");
				exit(EXIT_FAILURE);
			}
			/* Use letsprint for string concatenation*/
			letsprint(full_path);
			letsprint(token);
			letsprint("/");
			letsprint(command);
			/* Check if the command is executable*/
			if (access(full_path, X_OK) == 0)
			{
				/* Execute the command using execvp*/
				comargs[0] = strdup(full_path);
				if (comargs[0] == NULL)
				{
					perror("error in strdup");
					exit(EXIT_FAILURE);
				}
				free(full_path);
				return;
			}
			while (token != NULL)
			{
				free(full_path);
				token = strtok(NULL, ":");
			}
		}
		/*If the loop completes, the command was not found in PATH*/
		letsprint("Command not found in PATH: ");
		letsprint(command);
		letsprint("\n");
		exit(EXIT_FAILURE);
	}
	/* Set the rest of the arguments to NULL*/
	comargs[1] = NULL;
}
