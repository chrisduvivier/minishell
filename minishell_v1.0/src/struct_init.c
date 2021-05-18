/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 18:12:56 by cduvivie          #+#    #+#             */
/*   Updated: 2021/05/18 15:33:49 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_msh g_msh;

/*
**	initialize global var g_msh
*/

void    t_msh_init(void)
{
	g_msh.status = 1;
	g_msh.cmd_t = NULL;
	g_msh.env = NULL;
}

void	t_cmd_table_init(t_cmd_table *cmd_t)
{
	cmd_t->origin_cmd = NULL;
	cmd_t->cmd = NULL;
	cmd_t->opt = NULL;
	cmd_t->arg = NULL;
	cmd_t->in_file_fd = STDIN_FILENO;
	cmd_t->out_file_fd = STDOUT_FILENO;
	cmd_t->err_file_fd = STDERR_FILENO;
	cmd_t->in_file = NULL;
	cmd_t->out_file = NULL;
	cmd_t->next = NULL;
}
