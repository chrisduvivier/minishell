/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 17:07:07 by rlinkov           #+#    #+#             */
/*   Updated: 2021/06/11 00:50:46 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_msh	g_msh;

/*
**	Check if string cmd is one of the fd redirection.
*/

int	check_mode(char *cmd)
{
	int	mode;

	mode = 0;
	if (*cmd == RCHEVRON)
	{
		mode = 1;
		if (ft_strlen(cmd) == 2 && cmd[1] == RCHEVRON)
		{
			mode = 2;
		}
	}
	else if (*cmd == LCHEVRON)
		mode = 3;
	return (mode);
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
		ft_printf("minishell: cannot read %s\n", path);
	first_t_cmd->in_file_fd = fd;
}

/*
**	@params:
**		path: the name of the file to open/create
**		mode: 1 for '>', 2 for '>>'.
**
**		0666: to give permission 
*/

void	handle_output_redirect(t_cmd_table *last_t_cmd, char *path, int mode)
{
	int	flags;
	int	fd;

	if (mode == 1)
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	else if (mode == 2)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
	{
		ft_printf("minishell: wrong file mode %s\n", path);
		return ;
	}
	fd = open(path, flags, 0666);
	if (fd < 0)
		ft_printf("minishell: cannot create %s\n", path);
	last_t_cmd->out_file_fd = fd;
}

/*
**	Check for input output settings (>, <, >>)
*/

void	set_io_redirection(t_cmd_table *t_cmd, t_cmd_table *t_cmds, int len)
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
		else if (mode == 1 || mode == 2)
		{
			printf("mode [%d]\n", mode);
			handle_output_redirect(&t_cmds[len - 1], t_cmd->argv[i + 1], mode);
		}
		else if (mode == 3)
			handle_input_redirect(&t_cmds[0], t_cmd->argv[i + 1]);
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

void	check_redirections(t_cmd_table *t_cmds, int t_size)
{
	int	i;

	i = 0;
	while (i < t_size)
	{
		set_io_redirection(&t_cmds[i], t_cmds, t_size);
		clean_empty_arg(&t_cmds[i]);
		i++;
	}
}
