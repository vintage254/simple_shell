#include "shell.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
void replace_variables(char **args, const par_t *pars)
{
        int i;
        for (i = 0; args[i] != NULL; ++i)
        {
                /* Handle $? variable*/
                if (strcmp(args[i], "$?") == 0)
                {
                        char status_str[20];
                        snprintf(status_str, sizeof(status_str), "%d", pars->stats);
			if (args[i] != NULL)
			{
				free(args[i]);
			}
                        args[i] = strdup(status_str);
                }
                /* Handle $$ variable*/
                else if (strcmp(args[i], "$$") == 0)
                {
                        char pid_str[20];
                        snprintf(pid_str, sizeof(pid_str), "%d", getpid());
                        free(args[i]);
                        args[i] = strdup(pid_str);
                }
        }
}
void add_alias(par_t *pars, const char *name, const char *value)
{
        /* Check if an alias with the same name already exists*/
        alias_t *existing_alias = find_alias(pars, name);
        if (existing_alias != NULL)
        {
                /* Update the existing alias with the new value*/
                free(existing_alias->value);
                existing_alias->value = strdup(value);
        }
        else
        {
                /* Allocate memory for a new alias*/
                alias_t *new_alias = malloc(sizeof(alias_t));
                if (new_alias == NULL)
                {
                        perror("Error in malloc");
                        exit(EXIT_FAILURE);
                }
                /* Set the name and value for the new alias*/
                new_alias->name = (name != NULL) ? strdup(name) : NULL;
                new_alias->value = (value != NULL) ? strdup(value) : NULL;
                /* Add the new alias to the aliases array*/
                new_alias->next = pars->aliases;
                pars->aliases = new_alias;
        }
}
void print_aliases(const par_t *pars)
{
        /* Traverse the aliases linked list and print each alias*/
        alias_t *current_alias = pars->aliases;
        while (current_alias != NULL)
        {
                printf("%s='%s'\n", current_alias->name, current_alias->value);
                current_alias = current_alias->next;
        }
}
char *resolve_alias(const par_t *pars, const char *name)
{
        /* Find the alias with the specified name*/
        alias_t *alias = find_alias(pars, name);
        /* Return the alias value if found, otherwise return NULL*/
        return (alias != NULL) ? alias->value : NULL;
}
/* Helper function to find an alias by name*/
alias_t *find_alias(const par_t *pars, const char *name)
{
        alias_t *current_alias = pars->aliases;
        while (current_alias != NULL)
        {
                if (strcmp(current_alias->name, name) == 0)
                {
                        return current_alias;
                }
                current_alias = current_alias->next;
        }
        return NULL; /* Alias not found*/
}
/**
 * exec_prompt - Executes a command in a forked child process using execve
 * @stringcommand: The path to the executable file
 */
void exec_prompt(const char *stringcommand, par_t *pars)
{
	pid_t childprocess = fork();

	if (childprocess == -1)
	{
		perror("error in fork");
		exit(EXIT_FAILURE);
	}
	else if (childprocess == 0)
	{
		exec_child(stringcommand, pars);
	}
	else
	{
		exec_parent(childprocess);
	}
}

/**
 * exec_child - Function to execute child process using execve
 * @stringcommand: The path to the executable file
 */
void exec_child(const char *stringcommand, par_t *pars )
{
	/*Dynamically allocate memory for comargs*/
	char *comargs[2];
	comargs[0] = strdup(stringcommand);
	comargs[1] = NULL;

	/* Handle the "exit" command separately */
	if (strcmp(comargs[0], "exit") == 0)
	{
		forExit(pars);
		exit(EXIT_SUCCESS);
	}
	/* Handle the "setenv" command */
	else if (strcmp(comargs[0], "setenv") == 0)
	{
		setEnv(pars);
		exit(EXIT_SUCCESS);
	}
	/* Handle the "unsetenv" command */
	else if (strcmp(comargs[0], "unsetenv") == 0)
	{
		unsetEnv(pars);
		exit(EXIT_SUCCESS);
	}
	/* Handle the "cd" command */
	else if (strcmp(comargs[0], "cd") == 0)
	{
		cd(pars);
		exit(EXIT_SUCCESS);
	}
	/*handle path */
	handle_path(comargs[0], comargs);

	if (execve(comargs[0], comargs, environ) == -1)
	{
		perror("error in child process execve");
		exit(EXIT_FAILURE);
	}
	
	free(comargs[0]);
}
/**
 * exec_parent - Waits for the child process to complete and handles the status
 * @childprocess: The process ID of the child process
 *
 * This function waits for the child process specified by 'childprocess' to
 * complete its execution. It then examines the status of the child process and
 * prints an error message if the child process did not exit successfully.
 *
 * @childprocess: The process ID of the child process to wait for.
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
/**
 * setEnv - Initialize a new environment variable or modify an existing one
 * @pars: parameters including the command line arguments
 */
void setEnv(par_t *pars)
{
	if (pars->args[1] && pars->args[2])
	{
		if (setenv(pars->args[1], pars->args[2], 1) != 0)
		{
			perror("setenv");
		}
	}
	else
	{
		fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
	}
}
/**
 * unsetEnv - Remove an environment variable
 * @pars: parameters including the command line arguments
 */
void unsetEnv(par_t *pars)
{
	if (pars->args[1])
	{
		if (unsetenv(pars->args[1]) != 0)
		{
			perror("unsetenv");
		}
	}
	else
	{
		fprintf(stderr, "Usage: unsetenv VARIABLE\n");
	}
}
/**
 * cd - Changes the current directory of the process
 * @pars: parameters including the command line arguments
 */
void cd(par_t *pars)
{
	if (pars->args[1])
	{
		if (chdir(pars->args[1]) != 0)
		{
			perror("cd");
		}
		else
		{
			setenv("PWD", pars->args[1], 1);
		}
	}
	else
	{
		/* If no argument is given, change to the home directory*/
		char *home = getenv("HOME");
		if (home)
		{
			if (chdir(home) != 0)
			{
				perror("cd");
			}
			else
			{
				setenv("PWD", home, 1);
			}
		}
	}
}
