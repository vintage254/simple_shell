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

void letsprint (const char *commandline);
void allsmiles(void);
void exec_promt(const char *stringcommand);
int main(void);
void read_user_input(char *user_input, size_t x);

#endif
