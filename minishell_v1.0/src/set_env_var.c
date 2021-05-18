/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 15:27:33 by rlinkov           #+#    #+#             */
/*   Updated: 2021/05/18 16:12:54 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_msh g_msh;

/*
** Find the corresponding environment variable and return it
*/

char *find_var(char *var_name)
{
    char *var;
    int i;
    int len;

    i = 0;
    var = malloc(sizeof(char));
    if (!var)
        handle_error(ERR_MALLOC);
    var[0] = '\0';
    len = ft_strlen(var_name);
    while (g_msh.env[i] && g_msh.env[i] != NULL)
    {
        if (ft_strncmp(var_name, g_msh.env[i], len) == 0)
        {
            if (g_msh.env[i][len] && g_msh.env[i][len] == '=')
            {
                free(var);
                var = ft_strdup(g_msh.env[i] + len + 1);
                break;
            }
        }
        i++;
    }
    free(var_name);
    return (var);
}

/*
** Insert the environment variable value inside the command
*/

char *rebuild_cmd(char *full_cmd, int pos_i, char *var, int len_var_name)
{
    char *new_cmd;
    int i;
    int j;

    new_cmd = (char *)malloc(ft_strlen(var) - len_var_name + ft_strlen(full_cmd) + 1);
    i = 0;
    while (i < pos_i)
    {
        new_cmd[i] = full_cmd[i];
        i++;
    }
    while (*var && var)
    {
        new_cmd[i] = *var;
        var++;
        i++;
    }
    j = 0;
    while (full_cmd[pos_i + len_var_name + j])
    {
        new_cmd[i] = full_cmd[pos_i + len_var_name + j];
        i++;
        j++;
    }
    new_cmd[i] = '\0';
    free(full_cmd);
    return (new_cmd);
}

/*
** The purpose of this function is to substitute $VAR with the corresponding
** environment var if it exist and rebuild the command by inserting the right
** value inside
*/

char *set_env_var(char *full_cmd, int i)
{
    int len_var;
    int pos_i;
    char *var_name;
    char *var;

    pos_i = i;
    len_var = 0;
    while (full_cmd[i] != ' ' && full_cmd[i])
    {
        len_var++;
        i++;
    }
    var_name = malloc(sizeof(char) * (len_var));
    ft_strlcpy(var_name, full_cmd + pos_i + 1, len_var);
    var = find_var(var_name);
    // if (!var || !*var)
    //     full_cmd = rebuild_cmd(full_cmd, pos_i, "\0", len_var + 1);
    // else
    full_cmd = rebuild_cmd(full_cmd, pos_i, var, len_var);
    free(var);
    return (full_cmd);
}