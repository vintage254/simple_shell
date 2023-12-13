#include "shell.h"

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
		new_alias->name = strdup(name);
		new_alias->value = strdup(value);
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

