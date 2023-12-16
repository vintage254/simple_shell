#include "shell.h"
#include <stdlib.h>

/**
 * pathbuff - fills path buff
 * @pathbuffer: a buffer to store the path
 * @path: a path
 * @command: a command
 * Return: 1 (successful) or 0(fail)
 */

void pathbuff(char *pathbuffer, char *path, char *command)
{
	char *t = pathbuffer;

	while (*path)
	{
		*t = *path;
		t++;
		path++;
	}

	*t = '/';

	t++;
	/*concatenate command to t*/
	while (*command)
	{
		*t = *command;
		command++;
		t++;
	}
	*t = '\0';
}

/**
 * fillpath - fills path buff
 * @path_buff: a buffer to store the path
 * @path: a path
 * @command: a command
 * Return: 1 (successful) or 0(fail)
 */
int fillpath(char *path_buff, char *path, char *command)
{
	if (path_buff != NULL)
		pathbuff(path_buff, path, command);
	else
		return (0);
	return (1);
}

/**
 * relativepath - check if args[0] is a relative path
 * @arg: array of tokens
 * Return: 1 (true) and 0 (false)
*/
int relativepath(char **arg)
{
	if (arg[0][0] == '.' && arg[0][1] == '/')
		return (1);
	else if (arg[0][0] == '.' && arg[0][1] == '.' && arg[0][2] == '/')
		return (1);

	return (0);
}
/**
 * findpath - find the path of a command
 * @string: command
 * Return: the path to the command or NULL if command doesn't exist
 */
char *findpath(char *string)
{
	char *path_t, copy[1024], *pathbuffer, *command, *path;
	int get_path = 0;
	
	command = token_s(string, " ");
	path_t = getenv("PATH");
	if (path_t == NULL)
		return NULL;

	move(copy, path_t);
	pathbuffer = malloc(BUFFSIZE);
	if (!pathbuffer)
	{
		free(command);
		return NULL;
	}
	while ((path = token_s(copy, ":")))
	{
		pathbuff(pathbuffer, path, command);
		if (access(pathbuffer, X_OK) == 0)
		{
			get_path = 1;
			break;
		}
	}
	free(command);
	free(pathbuffer);
	
	return (get_path ? strdup(pathbuffer) : NULL);
}

/**
 * getpath - find the path of a command
 * @arg: array of tokens
 * @c: number of times shell has run
 * @argv: name of the shell
 * Return: the path to the command or NULL if command doesn't exist
 */
int getpath(char **arg, int c, char *argv)
{
	char *p = NULL;
	char temp[BUFFSIZE];

	move(temp, arg[0]);
	if (relativepath(arg))
	{
		p = handle_relative_path(arg, temp, c, argv);
		if (p == NULL)
		{
			fprintf(stderr, "%s: %d: %s: unaval\n", argv, c, temp);
			return (127);
		}
	}
	else if (arg[0][0] != '/')
	{
		char *path = findpath(arg[0]);

		if (path == NULL)
		{
			fprintf(stderr, "%s: %d: %s: not found\n", argv, c, temp);
			return (127);
		}

		free(arg[0]);
		arg[0] = path;
	}
	else
	{
		if (invalidpath(arg) == 127)
			return (127);
	}
	return (0);
}
