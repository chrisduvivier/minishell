/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 15:52:02 by rlinkov           #+#    #+#             */
/*   Updated: 2021/05/18 15:28:05 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_msh g_msh;

/*
** This function copies the content of the variable envp from the main
** into a new array of char that we can track, modify and use simplier
** during the execution of minishell
*/

void    copy_env(char **envp)
{
    char    **env;
    int     i;

    i = 0;
    while (envp[i] && envp)
        i++;
    env = (char **)malloc(sizeof(char *) * i + 1);
    if (env)
    {
        env[i] = NULL;
        i = 0;
        while (envp[i] && envp)
        {
            env[i] = ft_strdup(envp[i]);
            i++;
        }
    }
    g_msh.env = env;
}