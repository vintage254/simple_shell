#include "shell.h"

/**
 * getline_func - Reads a line of input from the user.
 * @user_input: Pointer to the buffer to store user input.
 * @x: Size of the buffer.
 * Return: Number of characters read (excluding null terminator).
 */
ssize_t getline_func(char *user_input, size_t x)
{
	static char buffer[BUFFER_SIZE];
	static size_t buffer_index = 0;
	static ssize_t chars_in_buffer = 0;
	ssize_t chars_read = 0;
	
	/* Refill the buffer if it's empty*/
	
	if (buffer_index >= (size_t)chars_in_buffer || buffer_index == 0)
	{
		chars_in_buffer = read(STDIN_FILENO, buffer, BUFFER_SIZE);
		if (chars_in_buffer == -1)
		{
			perror("read");
			exit(EXIT_FAILURE);
		}
		if (chars_in_buffer == 0)
		{
			/* End of file reached*/
			return -1;
		}
		buffer_index = 0;
	}
	/* Copy characters from the buffer to user_input until newline or buffer ends*/
	while (buffer_index < (size_t)chars_in_buffer && chars_read < (ssize_t)x - 1 && buffer[buffer_index] != '\n')
	{
		user_input[chars_read++] = buffer[buffer_index++];
	}
	/* Null-terminate the string*/
	user_input[chars_read] = '\0';
	/* Move to the next character in the buffer*/
	buffer_index++;
	return chars_read;
}
