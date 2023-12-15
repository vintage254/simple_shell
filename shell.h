#ifndef SHELL_H
#define SHELL_H
#include <errno.h>
#include <stdio.h>
#include <limits.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <stddef.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#define BUFFSIZE 1064

void _print(char *display);
void move(char *destination, char *source);
char *stringcopy(char *destination, char *strc);
int lengthstr(char *s);
char *strngocc(const char *string, const char *checkchar);
char *token_s(char *string, char *delmtr);
char *termi_null(char *input_string);
int char_check(char *input_string, char *env[], int c, char *argh);

#endif
