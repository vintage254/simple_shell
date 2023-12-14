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
 * struct alias - A structure to represent an alias in the shell
 * @name: The name of the alias
 * @value: The value associated with the alias
 * @next: Pointer to the next alias in the linked list
 *
 * Description: This structure is used to represent an alias in the shell.
 * It includes the name, which is the alias itself, the value, which is
 * the command or string the alias represents, and a pointer to the next
 * alias in the linked list.
 * struct alias - Represents an alias in the shell
 * @name: The name of the alias
 * @value: The value or command associated with the alias
 * @next: Pointer to the next alias in the linked list
 */
typedef struct alias
{
	char *name;
	char *value;
	struct alias *next;
} alias_t;
/**
 * struct pars - structure used to hold all shell variables needed
 * @argv: command line argument from main function
 * @args: array of arguments
 * @stats: run command return status
 * @aliases: pointer to a linked list of aliases
 * Description: Structures hold the variables that passed to
 * other functions.
 */
typedef struct pars
{
	char **argv;
	char **args;
	int stats;
	alias_t *aliases;
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
extern char **environ;

void exec_prompt(const char *stringcommand, par_t *pars);
void exec_child(const char *stringcommand, par_t *pars);
void exec_parent(pid_t childprocess);
void letsprint (const char *commandline);
void letsprint_int(int num);
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

void setEnv(par_t *pars);
void unsetEnv(par_t *pars);
void cd(par_t *pars);
void free_shell(par_t *shell);
void replace_variables(char **args, const par_t *pars);
void add_alias(par_t *pars, const char *name, const char *value);
void print_aliases(const par_t *pars);
char *resolve_alias(const par_t *pars, const char *name);
alias_t *find_alias(const par_t *pars, const char *name);
void exec_prompt(const char *stringcommand, par_t *pars);
void exec_child(const char *stringcommand, par_t *pars);
void exec_parent(pid_t childprocess);
int handle_builtin_commands(char **comargs, par_t *pars);
void handle_path_and_execute(char *comargs[2]);
void execute_command(char **comargs);
char *create_full_path(const char *directory, const char *command);

#endif
