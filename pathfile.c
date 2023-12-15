#include "shell.h"
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
	/*copy path to pathbuffer*/
	while (*path)
	{
		*t = *path;
		t++;
		path++;
	}
	*t = '/'; /*add a / to pathbuff*/

	t++;
	/*concatenate command to t*/
	while (*command)
	{
		*t = *command;
		command++;
		t++;
	}
	*t = '\0'; /*null terminate path_buff*/
}

/**
 * __fillpath - fills path buff
 * @_path_buff: a buffer to store the path
 * @path: a path
 * @cmd: a command
 * Return: 1 (successful) or 0(fail)
 */
int __fillpath(char *_path_buff, char *path, char *command)
{
	if (_path_buff != NULL)
		__fillpath(_path_buff, path, command);
	else
		return (0);
	return (1);
}

/**
 * relativepath - check if args[0] is a relative path
 * @arg: array of tokens
 * Return: 1 (true) / 0 (false)
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
	char *path_t, _copy[1024], *path, *pathbuffer, *command;
	int get_path = 0;

	command = token_s(string, " ");
	path_t = getenv("PATH");
	if (path_t == NULL)
		return (NULL);
	move(_copy, path_t);
	path = token_s(_copy, ":");
	if (command == NULL)
		return (NULL);
	if (*string != '/')
	{
		while (path)
		{
			pathbuffer = malloc(BUFFSIZE * sizeof(char));
			if (pathbuff(pathbuff, path, command) == 0)
				return (NULL);
			if (access(_path_buff, X_OK) == 0)
			{
				get_path = 1;
				break;
			}
			else
			{
				free(_path_buff);
			}
			path = token_s(NULL, ":");
		}
		if (get_path != 1)
		{
			return (NULL);
		}
	}
	else
	{
		pathbuff = malloc(sizeof(char) * (lengthstr(string) + 2 + lengthstr(path)));
		move(_path_buff, command);
	}
	return (_path_buff);
}

/**
 * path_finder - find the path of a command
 * @arg: array of tokens
 * @c: number of times shell has run
 * @argv: name of the shell
 * Return: the path to the command or NULL if command doesn't exist
 */
int getpath(char **arg, int c, char *argv)
{
	char *p;
	char temp[BUFFSIZE];

	move(temp, arg[0]);
	if (relativepath(arg))
	{
		p = realpath(arg[0], NULL);
		if (p != NULL)
		{
			free(arg[0]);
			arg[0] = p;
		}
		else
		{
			freeTokens(arg);
			fprintf(stderr, "%s: %d: %s: not found\n", argv, c, temp);
			return (127);
		}
	}
	else if (arg[0][0] != '/')
	{
		path = findpath(arg[0]);
		if (p == NULL)
		{
			freeTokens(arg);
			fprintf(stderr, "%s: %d: %s: not found\n", argv, c, temp);
			return (127);
		}
		else
		{
			free(arg[0]);
			arg[0] = p;
		}
	}
	else
	{

		if (invalidpath(arg) == 127)

		if (invalidpath(args) == 127)
			return (127);
	}
	return (0);
}
