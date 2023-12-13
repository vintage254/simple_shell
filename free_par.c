#include "shell.h"

/**
 * free_shell - Frees the memory allocated for the par_t structure.
 *
 * @params: pointer to the structure to free
 *
 * This function frees the dynamically allocated memory used by the shell_t
 * structure, including its members: the array of arguments, the aliases list,
 * and the input buffer.
 */

void free_shell(par_t *params)
{
	alias_t *current_alias;

	if (params == NULL)
	{
		return;
	}
	if (params->argv != NULL)
	{
		free(params->argv);
	}
	if (params->args != NULL)
	{
		int i;

		for (i = 0; params->args[i] != NULL; i++)
		{
			free(params->args[i]);
		}
		/*Free the args array itself*/
		free(params->args);
	}
	/*Free the aliases linked list*/
	current_alias = params->aliases;
	while (current_alias != NULL)
	{
		alias_t *next_alias = current_alias->next;

		free(current_alias->name);
		free(current_alias->value);
		free(current_alias);
		current_alias = next_alias;
	}
	/*Finally, free the params structure itself*/
	free(params);
}
