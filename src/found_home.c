/*
** EPITECH PROJECT, 2023
** mysh
** File description:
** minishell
*/

#include "mysh.h"

void found_home_and_path(var_t *var)
{
    bool found_home = false;
    bool found_path = false;

    for (unsigned int i = 0; var->env[i]; i++) {
        if (!found_home && !my_strncmp(var->env[i], "USER_ZDOTDIR=", 13)) {
            var->home = my_strdup(var->env[i] + 13);
            found_home = true;
        }
        if (!found_path && !my_strncmp(var->env[i], "PATH=", 5)) {
            var->path = NULL;
            var->path = my_strdup(var->env[i] + 5);
            found_path = true;
        }
        if (found_home && found_path)
            break;
    }
    if (!found_home)
        var->home = "/home/";
    parsing_path(var);
}
