/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 13:52:53 by cduvivie          #+#    #+#             */
/*   Updated: 2021/06/25 19:08:05 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_msh	g_msh;

void	free_t_cmd_helper(t_cmd_table *t_cmd)
{
	if (t_cmd->argc > 0 || t_cmd->argv != NULL)
	{
		free(t_cmd->argv);
		t_cmd->argv = NULL;
	}
	if (t_cmd->heredoc != NULL)
	{
		free(t_cmd->heredoc->eof_str);
		free(t_cmd->heredoc);
		t_cmd->heredoc = NULL;
	}
}

void	free_t_cmd(t_cmd_table *t_cmd)
{
	int	i;

	i = 0;
	if (t_cmd->cmd)
	{
		free(t_cmd->cmd);
		t_cmd->cmd = NULL;
	}
	if (t_cmd->cmd_abs_path)
	{
		free(t_cmd->cmd_abs_path);
		t_cmd->cmd_abs_path = NULL;
	}
	while (i <= t_cmd->argc)
	{
		free(t_cmd->argv[i]);
		t_cmd->argv[i] = NULL;
		i++;
	}
	free_t_cmd_helper(t_cmd);
	close_fd(t_cmd);
	free(t_cmd);
}

void	free_array_t_cmd(t_cmd_table **t_cmds, int len_t_cmds)
{
	int	i;

	i = 0;
	while (i <= len_t_cmds)
	{
		if (t_cmds)
		{
			free_t_cmd(t_cmds[i]);
			t_cmds = NULL;
		}
		i++;
	}
	free(t_cmds);
	t_cmds = NULL;
}

void	free_msh_and_exit(int exit_status)
{
	ft_split_free(g_msh.env);
	g_msh.env = NULL;
	if (g_msh.raw_cmds_len > 0 && g_msh.raw_cmds != NULL)
		free_array_str(g_msh.raw_cmds, g_msh.raw_cmds_len);
	if (g_msh.t_cmds_len > 0)
		free_array_t_cmd(g_msh.t_cmds, g_msh.t_cmds_len);
	update_history_file();
	if (exit_status == EXIT_SUCCESS && g_msh.status != 0)
	{
		exit(g_msh.status);
	}
	else
	{
		g_msh.status = exit_status;
		exit(exit_status);
	}
}
