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

#define BUFFSIZE 1024

#include <string.h>


#define BUFFSIZE 1064



void letsprint(const char *displaying);
void cshell(void);
void execute_command(char **arg, char *env[], int count, char *argv);
void read_command(char *command, size_t size);
int main(int __attribute__((unused)) argh, char *argv[], char *env[]);

int getpath(char **arg, int c, char *argv);
char *findpath(char *string);
int relativepath(char **arg);
void pathbuff(char *pathbuffer, char *path, char *command);

int _stringcmp(const char *string1, const char *string2);
int invalidpath(char **arg);
void freeTokens(char **tocken);
char **tokenizermspace(char *input);

static char **tokenize(const char *provided, int token_no);
static int no_of_tokens(const char *provided);
int __fillpath(char *_path_buff, char *path, char *command);
void pathbuff(char *pathbuffer, char *path, char *command);

char **tokenize(const char *provided, int token_no);
int no_of_tokens(const char *provided);


void _print(char *display);
void move(char *destination, char *source);
char *stringcopy(char *destination, char *strc);
int lengthstr(char *s);
char *strngocc(const char *string, const char *checkchar);
char *token_s(char *string, char *delmtr);
char *termi_null(char *input_string);
int char_check(char *input_string, char *env[], int c, char *argh);


#endif /*SHELL_H*/
>>>>>>> errors
