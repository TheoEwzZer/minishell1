/*
** EPITECH PROJECT, 2023
** mysh
** File description:
** minishell
*/

#include "mysh.h"

void builtin_env(char **str, var_t *var)
{
    int status = 0;
    if (!var->pid) {
        status = execve(var->cmd, str, var->env);
        exit(0);
    }
    wait(&status);
    if (str[1]) {
        free(var->cmd);
        unsigned int len_cmd = my_strlen(str[1]) + 6;
        var->cmd = malloc(sizeof(char) * my_strlen(str[1]) + 6);
        for (unsigned int i = 0; i < len_cmd; var->cmd[i] = '\0', i++);
        var->cmd = my_strcat(var->cmd, "/bin/");
        var->cmd = my_strcat(var->cmd, str[1]);
        if ((execve(var->cmd, str, var->env)) == -1) {
            write(2, "env: ‘", 8); write(2, str[1], my_strlen(str[1]));
            write(2, "’: No such file or directory\n", 31);
            free_var(var); exit(127);
        }
    }
    my_show_word_array(var->env);
}
