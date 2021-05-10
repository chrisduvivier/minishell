/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 18:12:56 by cduvivie          #+#    #+#             */
/*   Updated: 2021/05/10 18:58:46 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    t_msh_init(t_msh *msh)
{
	msh->status = 1;
	msh->cmd_t = NULL;
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
