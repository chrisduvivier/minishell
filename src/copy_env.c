/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlinkov <rlinkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 15:52:02 by rlinkov           #+#    #+#             */
/*   Updated: 2021/06/07 16:23:51 by rlinkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_msh g_msh;

/*
** This function copies the content of the variable envp from the main
** into a new array of char that we can track, modify and use simplier
** during the execution of minishell
*/

void    copy_key_value(char *env, char *key, char *value)
{
    int i;
    int len_k;
    int len_t;
    
    i = 0;
    len_k = ft_strlen(key);
    len_t = ft_strlen(key) + ft_strlen(value) + 1;
    while (i < len_k)
    {
        env[i] = *key;
        key++;
        i++;
    }
    env[i] = '=';
    i++;
    while (i < len_t)
    {
        env[i] = *value;
        value++;
        i++;
    }
    env[i] = '\0';
}

void    set_env_value(char *key, char *value)
{
    int i;
    int len;

    i = 0;
    len = ft_strlen(key);
    while (g_msh.env[i] && g_msh.env[i] != NULL)
    {
        if (ft_strncmp(key, g_msh.env[i], len) == 0)
        {
            if (g_msh.env[i][len] && g_msh.env[i][len] == '=')
            {
                free(g_msh.env[i]);
                g_msh.env[i] = malloc(ft_strlen(key) + ft_strlen(value) + 2); //+1 for '\0' and +1 for =
                copy_key_value(g_msh.env[i], key, value);
                break;
            }
        }
        i++;
    }
}

void    set_shlvl()
{
    char *shlvl;
    int shlvl_int;

    shlvl = find_var("SHLVL");
    shlvl_int = ft_atoi(shlvl);
    shlvl_int = shlvl_int + 1;
    shlvl = ft_itoa(shlvl_int);
    set_env_value("SHLVL", shlvl);
    free(shlvl);
}

void    copy_env(char **envp)
{
    char    **env;
    int     i;

    i = 0;
    while (envp[i] && envp)
        i++;
    env = (char **)malloc(sizeof(char *) * i + 1);
    if (!env)
        exit(MALLOC_FAILURE);       // might need to call for free function
    env[i] = NULL;
    i = 0;
    while (envp[i] && envp)
    {
        env[i] = ft_strdup(envp[i]);
        i++;
    }
    env[i] = NULL;
    g_msh.env = env;
    set_shlvl();
}