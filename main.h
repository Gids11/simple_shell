#ifndef _MAIN_H_
#define _MAIN_H_

#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#define END_OF_FILE -2
#define EXIT -3

extern char **environ;

char *name;

int hist;

/**
 * struct list_s - A new struct type defining a linked list.
 * @dir: A directory path.
 * @next: A pointer to another struct list_s.
 */
typedef struct list_s
{
	char *dir;
	struct list_s *next;
} list_t;

/**
 * struct builtin_s - A new struct type defining builtin commands.
 * @name: The name of the builtin command.
 * @f: A function pointer to the builtin command's function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(char **argv, char **out);
} builtin_t;

/**
 * struct alias_s - A new struct defining aliases.
 * @name: The name of the alias.
 * @value: The value of the alias.
 * @next: A pointer to another struct alias_s.
 */
typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next;
} alias_t;


alias_t *aliases;

ssize_t _getline_(char **lineptr, size_t *n, FILE *stream);
void *_realloc_(void *ptr, unsigned int old_size, unsigned int new_size);
char **_strtok_(char *line, char *delim);
char *_locator(char *command);
list_t *_path_dir(char *path);
int exec(char **args, char **out);
void free_list_(list_t *head);
char *_itoa_(int num);

void _handle_line(char **line, ssize_t read);
void variable_change(char **args, int *exe_ret);
char *getargs(char *line, int *exe_ret);
int callargs(char **args, char **out, int *exe_ret);
int runargs(char **args, char **out, int *exe_ret);
int args_handler(int *exe_ret);
int checkargs(char **args);
void freeargs(char **args, char **out);
char **_aliases_(char **args);

int str_len(const char *s);
char *str_cat(char *dest, const char *src);
char *strn_cat(char *dest, const char *src, size_t num);
char *str_cpy(char *dest, const char *src);
char *str_chr(char *s, char c);
int str_spn(char *s, char *a);
int str_cmp(char *s1, char *s2);
int strn_cmp(const char *s1, const char *s2, size_t num);

int (*set_builtin(char *command))(char **args, char **out);
int shell_exit(char **args, char **out);
int shell_env(char **args, char __attribute__((__unused__)) **out);
int shell_setenv(char **args, char __attribute__((__unused__)) **out);
int shell_unsetenv(char **args, char __attribute__((__unused__)) **out);
int shell_cd(char **args, char __attribute__((__unused__)) **out);
int shell_alias(char **args, char __attribute__((__unused__)) **out);
int shell_help(char **args, char __attribute__((__unused__)) **out);

char **copy_env(void);
void env_free(void);
char **get_env(const char *var);


int get_error(char **args, int err);
char *env_error(char **args);
char *_error_(char **args);
char *exit_error(char **args);
char *cd_error(char **args);
char *syntax_error(char **args);
char *_error_126(char **args);
char *_error_127(char **args);


alias_t *end_alias(alias_t **head, char *name, char *value);
void freealias(alias_t *head);
list_t *add_node(list_t **head, char *dir);
void free_list_(list_t *head);

void _all(void);
void _alias(void);
void _cd(void);
void _exit_(void);
void _help(void);
void _env(void);
void _setenv(void);
void _unsetenv(void);
void _history(void);

void fix_alias(char *var_name, char *value);
void alias_print(alias_t *alias);
ssize_t _new_len(char *line);
void logicals(char *line, ssize_t *new_len);
list_t *path_dir(char *path);
void sig_args(int s);


int proc_commands(char *file_path, int *exe_ret);
#endif
