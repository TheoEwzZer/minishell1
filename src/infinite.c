/*
** EPITECH PROJECT, 2023
** mysh
** File description:
** minishell
*/

#include "mysh.h"

void check(char **str, var_t *var)
{
    int status = 0;

    if (!var->pid) {
        if ((status = execve(var->cmd, str, var->env)) == -1)
            try_path(str, var);
    }
    wait(&status);
    handle_errors(status, var);
}

void choose_cmd(char **str, var_t *var)
{
    if (!my_strncmp(var->input, "cd", 2)) {
        builtin_cd(str, var);
        return;
    }
    if (!my_strncmp(var->input, "exit", 4)) {
        builtin_exit(str, var);
        return;
    }
    if (!my_strncmp(var->input, "unsetenv", 8)) {
        builtin_unsetenv(str, var);
        return;
    }
    if (!my_strncmp(var->input, "setenv", 6)) {
        builtin_setenv(str, var);
        return;
    }
    if (!my_strncmp(var->input, "env", 3)) {
        builtin_env(str, var);
        return;
    } check(str, var);
}

void wait_cmd2(unsigned int len_cmd, char **str, var_t *var)
{
    for (unsigned int i = 0; i < len_cmd; var->cmd[i] = '\0', i++);
    if (str[0][0] != '.' && str[0][0] != '/') {
        if (var->actu_path)
            var->cmd = my_strcat(var->cmd, var->actu_path);
        var->cmd = my_strcat(var->cmd, "/");
    }
    var->cmd = my_strcat(var->cmd, str[0]);
    var->pid = fork();
    if (var->pid == -1) {
        exit(1);
    } else {
        choose_cmd(str, var);
        free(var->cmd);
        var->cmd = NULL;
        free(var->input);
        var->input = NULL;
        for (unsigned int i = 0; str[i]; i++)
            free(str[i]);
        free(str);
    }
}

void wait_cmd(char **env, var_t *var)
{
    char **str = NULL;
    var->cmd = NULL;
    unsigned int len_cmd = 0;

    write(1, "$> ", 3);
    var->input = NULL; size_t len = 0;
    if (getline(&var->input, &len, stdin) == -1)
        exit(1);
    if (my_strlen(var->input) <= 1) {
        free(var->input);
        var->input = NULL;
        wait_cmd(env, var);
        return;
    }
    str = my_str_to_word_array(var->input);
    len_cmd = my_strlen(str[0]) + my_strlen(var->actu_path) + 2;
    var->cmd = malloc(sizeof(char) * len_cmd);
    if (!var->cmd)
        exit(1);
    wait_cmd2(len_cmd, str, var);
}
