/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 18:12:56 by cduvivie          #+#    #+#             */
/*   Updated: 2021/06/12 17:20:00 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_msh	g_msh;

/*
 **	initialize global var g_msh
 */

void	t_msh_init(void)
{
	g_msh.status = 0;
	g_msh.t_cmds = NULL;
	g_msh.t_cmds_len = 0;
	g_msh.raw_cmds = NULL;
	g_msh.raw_cmds_len = 0;
	g_msh.env = NULL;
}

void	t_cmd_table_init(t_cmd_table *cmd_t)
{
	cmd_t->cmd = NULL;
	cmd_t->cmd_abs_path = NULL;
	cmd_t->argv = NULL;
	cmd_t->argc = 0;
	cmd_t->in_file_fd = STDIN_FILENO;
	cmd_t->out_file_fd = STDOUT_FILENO;
	cmd_t->heredoc = NULL;
}
