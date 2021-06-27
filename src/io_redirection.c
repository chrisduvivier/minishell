/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 17:07:07 by rlinkov           #+#    #+#             */
/*   Updated: 2021/06/27 02:01:47 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_msh	g_msh;

/*
**	Check if string cmd is one of the fd redirection.
**	Supports: `>` `>>` `<` `<<`
*/

int	check_mode(char *cmd)
{
	int	mode;

	mode = 0;
	if (*cmd == RCHEVRON)
	{
		mode = RCHEVRON;
		if (ft_strlen(cmd) == 2 && cmd[1] == RCHEVRON)
		{
			mode = DOUBLE_RCHEVRON;
		}
	}
	else if (*cmd == LCHEVRON)
	{
		mode = LCHEVRON;
		if (ft_strlen(cmd) == 2 && cmd[1] == LCHEVRON)
		{
			mode = DOUBLE_LCHEVRON;
		}
	}
	return (mode);
}

/*
**	@params:
**		path: the name of the file to open
*/

void	handle_input_redirect(t_cmd_table *first_t_cmd, char *path)
{
	int	fd;

	if (!path)
	{
		handle_error("minishell: not valid filename", EXIT_FAILURE);
		first_t_cmd->out_file_fd = -1;
		return ;
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: cannot read '", STDERR_FILENO);
		if (path)
			ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd("'", STDERR_FILENO);
		handle_error("", EXIT_FAILURE);
	}
	first_t_cmd->in_file_fd = fd;
}

/*
**	@params:
**		path: the name of the file to open/create
**
**		0666: to give permission 
*/

void	handle_output_redirect(t_cmd_table *last_t_cmd, char *path, int mode)
{
	int	flags;
	int	fd;

	if (!path)
	{
		handle_error("minishell: not valid filename", EXIT_FAILURE);
		last_t_cmd->out_file_fd = -1;
		return ;
	}
	if (mode == RCHEVRON)
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	else if (mode == DOUBLE_RCHEVRON)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	fd = open(path, flags, 0666);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: cannot open '", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd("'", STDERR_FILENO);
		handle_error("", EXIT_FAILURE);
	}
	last_t_cmd->out_file_fd = fd;
}

/*
**	Check for input output settings (>, <, >>)
*/

void	set_io_redirection(t_cmd_table *t_cmd, t_cmd_table **t_cmds, int len)
{
	int	i;
	int	mode;

	i = 0;
	while (i < t_cmd->argc)
	{
		mode = check_mode(t_cmd->argv[i]);
		if (mode == 0)
		{
			i++;
			continue ;
		}
		else if (mode == RCHEVRON || mode == DOUBLE_RCHEVRON)
		{
			handle_output_redirect(t_cmds[len - 1], t_cmd->argv[i + 1], mode);
		}
		else if (mode == LCHEVRON)
			handle_input_redirect(t_cmds[0], t_cmd->argv[i + 1]);
		else if (mode == DOUBLE_LCHEVRON)
			handle_heredoc(t_cmds[0], t_cmd->argv[i + 1], len);
		free(t_cmd->argv[i]);
		t_cmd->argv[i++] = ft_strdup("");
		free(t_cmd->argv[i]);
		t_cmd->argv[i++] = ft_strdup("");
	}
}

/*
**	@param:
**		t_cmds	table of single commands
**		t_size	size of the table (array of t_cmd)
*/

void	check_redirections(t_cmd_table **t_cmds, int t_size)
{
	int	i;

	i = 0;
	while (i < t_size && t_cmds[i] != NULL)
	{
		set_io_redirection(t_cmds[i], t_cmds, t_size);
		clean_empty_arg(t_cmds[i]);
		i++;
	}
}
