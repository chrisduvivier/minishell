/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 11:13:35 by cduvivie          #+#    #+#             */
/*   Updated: 2021/06/25 19:18:11 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_msh	g_msh;

/*
**	close the fds if they are piped (therefore diff from 0 and 1)
**	@params:
**		t_cmd: single command table
*/

void	close_fd(t_cmd_table *t_cmd)
{
	if (t_cmd->in_file_fd > 0)
		close(t_cmd->in_file_fd);
	if (t_cmd->out_file_fd > 1)
		close(t_cmd->out_file_fd);
}

/*
**	redirect the STDIN and STDOUT to the ones specified in t_cmd
**	@description:
**		dup2: make fd2 point to fd1. This allows to write in a file fd1 even if
**			  the write function writes on STDOUT.
**	@params:
**		t_cmd: single command table 
*/

void	redirect_io(t_cmd_table *t_cmd)
{
	if (t_cmd->in_file_fd != STDIN_FILENO)
		dup2(t_cmd->in_file_fd, STDIN_FILENO);
	if (t_cmd->out_file_fd != STDOUT_FILENO)
		dup2(t_cmd->out_file_fd, STDOUT_FILENO);
}

/*
**	Iterate over piped commands and set their io fd.
**	@param:
**		t_cmds	table of single commands
**		t_size	size of the table (array of t_cmd)
*/

void	set_pipes(t_cmd_table **t_cmds, int t_size)
{
	int	i;
	int	fd_pipe[2];

	i = 0;
	while (i < t_size && t_cmds[i] != NULL)
	{
		if (i != 0)
		{
			pipe(fd_pipe);
			t_cmds[i - 1]->out_file_fd = fd_pipe[1];
			t_cmds[i]->in_file_fd = fd_pipe[0];
		}
		if (i == t_size - 1)
		{
			t_cmds[i]->out_file_fd = STDOUT_FILENO;
		}
		++i;
	}
}
