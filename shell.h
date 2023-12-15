#ifndef SHELL_H
#define SHELL_H
#include <stddef.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>

void letsprint(const char *message);
void cshell(void);
int main(void);
void read_command(char *command, size_t size);
void execute_command(const char*command);

#endif
