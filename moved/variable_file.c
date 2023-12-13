#include "shell.h"
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
			free(args[i]);
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
