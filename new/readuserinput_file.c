#include "shell.h"
/**
 * read_user_input - Reads user input from stdin
 * @user_input: Pointer to the buffer to store user input
 * @x: Size of the buffer
 */
void read_user_input(char *user_input, size_t x)
{
	if (fgets(user_input, x, stdin) == NULL)
	{
		if (feof(stdin))
		{
			letsprint("\n");
			exit(EXIT_SUCCESS);
		}
		else
		{
			letsprint("error in stdin, \n");
			exit(EXIT_FAILURE);
		}
	}
	user_input[strcspn(user_input, "\n)")] = '\0';
}
