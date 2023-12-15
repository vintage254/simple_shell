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
void execute_command(char **arg, char *env[], int count, char *argv)
void read_command(char *command, size_t size);
int main(int __attribute__((unused)) argh, char *argv[], char *env[]);

int getpath(char **arg, int c, char *argv);
char *findpath(char *string);
int relativepath(char **arg);
int __fillpath(char *_path_buff, char *path, char *command);
void pathbuff(char *pathbuffer, char *path, char *command);

int _stringcmp(const char *string1, const char *string2);
int invalidpath(char **args);
void freeTokens(char **tocken);
char **tokenizermspace(char *input);
static char **tokenize(const char *provided, int token_no);
static int no_of_tokens(const char *provided);

#endif
