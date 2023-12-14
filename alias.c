#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * find_alias - Find an alias in the aliases linked list by name.
 * @pars: Parameters including the aliases linked list.
 * @name: Name of the alias to find.
 * Return: NULL if alias not found else 0
 */
alias_t *find_alias(const par_t *pars, const char *name)
{
	alias_t *current_alias = pars->aliases;

	while (current_alias != NULL)
	{
		if (strcmp(current_alias->name, name) == 0)
		{
			return (current_alias);
		}
		current_alias = current_alias->next;
	}
	return (NULL); /* Alias not found*/
}
/**
 * add_alias - Add or update an alias in the aliases linked list.
 * @pars: Parameters including the aliases linked list.
 * @name: Name of the alias to add or update.
 * @value: Value of the alias.
 */
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
		/* Check if strdup failed for name or value */
		
		if ((name != NULL && new_alias->name == NULL) 
				|| (value != NULL && new_alias->value == NULL))
		{
			perror("Error in strdup");
			free(new_alias->name);  
			/* Free the allocated memory for name*/
			free(new_alias->value); 
			/* Free the allocated memory for value*/
			free(new_alias);
			/* Free the allocated memory for the new_alias structure*/
			exit(EXIT_FAILURE);
		}
		/* Add the new alias to the aliases array*/
		new_alias->next = pars->aliases;
		pars->aliases = new_alias;
	}
}
/**
 * print_aliases - Print all aliases in the aliases linked list.
 * @pars: Parameters including the aliases linked list.
 */
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
/**
 * resolve_alias - Resolve the value of an alias by name.
 * @pars: Parameters including the aliases linked list.
 * @name: Name of the alias to resolve.
 * Return: 0
 */
char *resolve_alias(const par_t *pars, const char *name)
{
	/* Find the alias with the specified name*/
	alias_t *alias = find_alias(pars, name);
	/* Return the alias value if found, otherwise return NULL*/
	return ((alias != NULL) ? alias->value : NULL);
}
