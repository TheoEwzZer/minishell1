/*
** EPITECH PROJECT, 2023
** mysh
** File description:
** minishell
*/

#include "mysh.h"

void remove_env(char **str, unsigned int j, var_t *var)
{
    bool found = false;
    unsigned int len = my_strlen(str[j]);

    for (unsigned int i = 0; var->env[i]; i++) {
        if (!my_strncmp(var->env[i], str[j], len) && var->env[i][len] == '=')
            found = true;
        if (found)
            var->env[i] = var->env[i + 1] ? var->env[i + 1] : NULL;
    }
}

void builtin_unsetenv(char **str, var_t *var)
{
    int status = 0;

    if (!var->pid) {
        status = execve(var->cmd, str, var->env); exit(0);
    }
    wait(&status); handle_errors(status, var);
    if (!str[1]) {
        write(2, "unsetenv: Too few arguments.\n", 29);
        free_var(var);
        exit(1);
    }
    for (unsigned int j = 1; str[j]; j++)
        remove_env(str, j, var);
}
