/*
** EPITECH PROJECT, 2023
** mysh
** File description:
** minishell
*/

#include "mysh.h"

char *create_new_cwd(char *cwd, var_t *var)
{
    char *new_cwd = NULL;
    unsigned int len = my_strlen(cwd) + 5;

    new_cwd = malloc(sizeof(char) * len);
    if (!new_cwd)
        return NULL;
    for (unsigned int i = 0; i < len; i++)
        new_cwd[i] = '\0';
    new_cwd = my_strcat(new_cwd, "PWD=");
    new_cwd = my_strcat(new_cwd, cwd);
    return new_cwd;
}

void change_cwd(char **str, var_t *var)
{
    bool has_changed = false;

    if (str[1] && (!my_strcmp(str[1], "home") || !my_strcmp(str[1], "~"))) {
        chdir(var->home);
        has_changed = true;
    } else if (str[1] && !my_strcmp(str[1], "-")) {
        chdir(var->old_cwd);
        has_changed = true;
    }
    if (str[1] && !has_changed)
        chdir(str[1]);
    else if (!has_changed)
        chdir(var->home);
}

char **replace_cwd(char *new_cwd, var_t *var)
{
    unsigned int len = my_strlen_double(var->env);
    char **str = malloc(sizeof(char *) * (len + 1));

    if (!str || !new_cwd)
        return NULL;
    for (unsigned int i = 0; var->env[i]; i++) {
        if (!my_strncmp(var->env[i], "PWD=", 4))
            str[i] = new_cwd;
        else
            str[i] = my_strdup(var->env[i]);
    }
    str[len] = 0;
    return str;
}

void builtin_cd(char **str, var_t *var)
{
    int status = 0;

    if (!var->pid) {
        status = execve(var->cmd, str, var->env);
        exit(0);
    }
    if (str[1] && my_strcmp(str[1], "-")) {
        free(var->old_cwd);
        var->old_cwd = my_strdup(getcwd(NULL, 0));
    }
    wait(&status);
    handle_errors(status, var);
    if (str[1])
        handle_errors_cd(str, var);
    change_cwd(str, var);
    char *cwd = getcwd(NULL, 0);
    var->env = replace_cwd(create_new_cwd(cwd, var), var);
}
