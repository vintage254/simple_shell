#ifndef SHELL_H
#define SHELL_H

#define BUFFER_SIZE 1024
#include <stddef.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
/**
 * struct pars - structure used to hold all shell variables needed
 * @argv: command line argument from main function
 * @args: array of arguments
 * @stats: run command return status
 * Description: Structures hold the variables that passed to
 * other functions.
 */
typedef struct pars
{
        char **argv;
        char **args;
        int stats;
} par_t;

/**
 * struct op - a buildin function
 * @name: buildin name
 * @func: pointer to buildin function
 */
typedef struct op
{
        char *name;
        void (*func)(par_t *);
} op_t;

void letsprint (const char *commandline);
void allsmiles(void);
void exec_promt(const char *stringcommand);
int main(void);
void read_user_input(char *user_input, size_t x);
void tokens(const char *commandline, char **args);
void handle_path(const char *command, char **comargs);
int validnumber(char *s);
void forExit(par_t *pars);
void forEnv(void);
ssize_t getline_func(char *user_input, size_t x);
void tokens_(const char *commandline, char **args);

#endif
