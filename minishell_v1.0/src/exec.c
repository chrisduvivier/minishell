/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlinkov <rlinkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 17:01:52 by rlinkov           #+#    #+#             */
/*   Updated: 2021/04/30 17:15:00 by rlinkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    exec_cmd(char *cmd) //sert juste d'exemple
{
    int i;
    char **arg;

    i = 0;
    arg = ft_split_msh(cmd, SPACE);
    while (arg[i] != NULL)
    {
        if (i == 0)
            printf("----------->CMD[%i] : |%s|\n", i, arg[i]);
        else
            printf("----------->ARG[%i] : |%s|\n", i, arg[i]);
        i++;
    }
    printf("\n");
}