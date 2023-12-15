#ifndef SHELL_H_
#define SHELL_H_

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

#define BUFFSIZE 1024

void letsprint(const char *displaying);
int getpath(char **arg, int c, char *argv);
char *findpath(char *string);
void pathbuff(char *pathbuffer, char *path, char *command);
int stringcmp(const char *string1, const char *string2);
static int no_of_tokens(const char *input_string);
static char **tokenize(const char *input_string, int token_no);
int invalidpath(char **arg);
void freeTokens(char **tocken);
char **tokenizermspace(char *input_string);
int fillpath(char *path_buff, char *path, char *command);
void pathbuff(char *pathbuffer, char *path, char *command);
char **tokenize(const char *input_string, int token_no);
int no_of_tokens(const char *input_string);
void _print(char *display);
void move(char *destination, char *source);
char *stringcopy(char *destination, char *strc);
int lengthstr(char *s);
char *strngocc(const char *string, const char *checkchar);
char *token_s(char *string, char *delmtr);
char *termi_null(char *input_string);
int char_check(char *input_string, char *env[], int c, char *argv);
void env_print(char *env[]);

#endif /*SHELL_H*/
