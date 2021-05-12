/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlinkov <rlinkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 15:52:02 by rlinkov           #+#    #+#             */
/*   Updated: 2021/05/11 16:17:30 by rlinkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** This function copies the content of the variable envp from the main
** into a new array of char that we can track, modify and use simplier
** during the execution of minishell
*/

void    copy_env(t_msh *msh, char **envp)
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
    msh->env = env;
}