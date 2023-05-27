/*
** EPITECH PROJECT, 2023
** mysh
** File description:
** minishell
*/

#include "mysh.h"

char **my_strdup_double(char **src, char *env_to_set)
{
    unsigned int i = 0;
    unsigned int len = my_strlen_double(src);
    char **str = malloc(sizeof(char *) * (unsigned long)(len + 2));

    for (i = 0; src[i]; i++)
        str[i] = my_strdup(src[i]);
    for (unsigned int j = i; j < i + 1; j++)
        str[j] = env_to_set;
    str[len + 1] = 0;
    return str;
}

char *create_new_env(char **str, var_t *var)
{
    char *new_env = NULL;
    unsigned int len = 0;

    if (str[2]) {
        len = my_strlen(str[1]) + 1 + my_strlen(str[2]) + 1;
        new_env = malloc(sizeof(char) * (unsigned long)len);
        for (unsigned int i = 0; i < len; i++)
            new_env[i] = '\0';
        new_env = my_strcat(new_env, str[1]);
        new_env = my_strcat(new_env, "=");
        new_env = my_strcat(new_env, str[2]);
    } else {
        len = my_strlen(str[1]) + 1 + 1;
        new_env = malloc(sizeof(char) * (unsigned long)len);
        for (unsigned int i = 0; i < len; i++)
            new_env[i] = '\0';
        new_env = my_strcat(new_env, str[1]);
        new_env = my_strcat(new_env, "=");
    }
    return new_env;
}

int isalphanum(char *str)
{
    int space = 0;
    for (int i = 0; str[i] && space < 2; i++) {
        if (str[i] == ' ')
            space++;
        if (str[i] > 96 && str[i] < 123)
            continue;
        if (str[i] > 47 && str[i] < 59)
            continue;
        if (str[i] > 64 && str[i] < 91)
            continue;
        if (str[i] == ' ')
            continue;
        if (str[i] == '\n')
            continue;
        if (str[i] == '/')
            continue;
        return 0;
    }
    return 1;
}

void builtin_setenv(char **str, var_t *var)
{
    bool found = false;
    char *new_env = NULL;
    int status = 0;
    if (!var->pid) {
        status = execve(var->cmd, str, var->env); exit(0);
    }
    wait(&status);
    handle_errors(status, var);
    if (handle_errors_setenv(str, var) == 84)
        return;
    var->modify_env = true;
    new_env = create_new_env(str, var);
    for (int i = 0; var->env[i]; i++) {
        if (!my_strncmp(var->env[i], new_env, my_strlen(str[1]) + 1)) {
            var->env[i] = new_env; found = true;
            found_home_and_path(var);
            break;
        }
    }
    var->env = found ? var->env : my_strdup_double(var->env, new_env);
}
