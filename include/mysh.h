/*
** EPITECH PROJECT, 2022
** mysh.h
** File description:
** mysh
*/

#ifndef MYSH_H_

    #define MYSH_H_

    #include "my.h"
    #include <signal.h>
    #include <stdbool.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <sys/stat.h>
    #include <sys/wait.h>
    #include <unistd.h>
    #include <errno.h>

typedef struct var {
    bool modify_env;
    char **env;
    char *actu_path;
    char *cmd;
    char *cwd;
    char *home;
    char *input;
    char *old_cwd;
    char *path;
    int return_value;
    pid_t pid;
} var_t;

char **my_strdup_double(char **src, char *env_to_set);
char **replace_cwd(char *new_cwd, var_t *var);
char *create_new_cwd(char *cwd, var_t *var);
char *create_new_env(char **str, var_t *var);
int check_command_not_found(char **str, var_t *var);
int handle_errors_setenv(char **str, var_t *var);
int isalphanum(char *str);
int my_char_isalpha(char c);
int starts_with_digit_and_has_alnum(char *str);
void builtin_cd(char **str, var_t *var);
void builtin_env(char **str, var_t *var);
void builtin_exit(char **str, var_t *var);
void builtin_exit2(char **str, var_t *var);
void builtin_setenv(char **str, var_t *var);
void builtin_unsetenv(char **str, var_t *var);
void change_cwd(char **str, var_t *var);
void check(char **str, var_t *var);
void check_arg(int argc, char **argv);
void check_not_found_and_close(char **str, var_t *var);
void choose_cmd(char **str, var_t *var);
void choose_cmd_mouli(char **str, var_t *var);
void cmd_mouli(var_t *var);
void create_cmd(var_t *var, char **str);
void found_home_and_path(var_t *var);
void free_env(var_t *var);
void free_var(var_t *var);
void handle_errors(int status, var_t *var);
void handle_errors_cd(char **str, var_t *var);
void parsing_path(var_t *var);
void remove_env(char **str, unsigned int j, var_t *var);
void try_path(char **str, var_t *var);
void wait_cmd(char **env, var_t *var);
void wait_cmd2(unsigned int len_cmd, char **str, var_t *var);

#endif /* MYSH_H_ */
