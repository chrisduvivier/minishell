/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 13:52:53 by cduvivie          #+#    #+#             */
/*   Updated: 2021/06/11 00:52:38 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_msh	g_msh;

void	free_t_cmd(t_cmd_table *t_cmd)
{
	int	i;

	i = 0;
	if (t_cmd->cmd)
		free(t_cmd->cmd);
	while (i < t_cmd->argc)
	{
		if (t_cmd->argv[i] != NULL)
			free(t_cmd->argv[i]);
		i++;
	}
	if (t_cmd->argv != NULL)
		free(t_cmd->argv);
}

void	free_msh_and_exit(int exit_status)
{
	if (g_msh.env)
	{
		ft_split_free(g_msh.env);
		g_msh.env = NULL;
	}
	if (exit_status == 0 && g_msh.status != 0)
		exit(g_msh.status);
	else
	{
		g_msh.status = exit_status;
		exit(exit_status);
	}
}
