/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 17:07:07 by rlinkov           #+#    #+#             */
/*   Updated: 2021/06/25 01:56:52 by cduvivie         ###   ########.fr       */
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

void	handle_heredoc(t_cmd_table *first_t_cmd, char *eof_str, int pipe_len)
{
	t_heredoc	*heredoc;
	int			fd;

	heredoc = (t_heredoc *)ft_calloc(1, sizeof(t_heredoc));
	if (heredoc == NULL)
		handle_error(ERR_MALLOC, MALLOC_FAILED);
	heredoc->eof_str = ft_strdup(eof_str);
	heredoc->pipe_len = pipe_len - 1;
	if (heredoc->eof_str == NULL)
		handle_error(ERR_MALLOC, MALLOC_FAILED);
	fd = open(TMP_FILE_NAME, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
		printf("minishell: cannot create %s\n", TMP_FILE_NAME);
	heredoc->tmp_file_fd = fd;
	first_t_cmd->heredoc = heredoc;
}

/*
**	@params:
**		path: the name of the file to open
*/

void	handle_input_redirect(t_cmd_table *first_t_cmd, char *path)
{
	int	fd;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		printf("minishell: cannot read %s\n", path);
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

	if (mode == RCHEVRON)
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	else if (mode == DOUBLE_RCHEVRON)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
	{
		printf("minishell: wrong file mode %s\n", path);
		return ;
	}
	fd = open(path, flags, 0666);
	if (fd < 0)
		printf("minishell: cannot create %s\n", path);
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
