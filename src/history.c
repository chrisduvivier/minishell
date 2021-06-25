/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 11:22:00 by cduvivie          #+#    #+#             */
/*   Updated: 2021/06/25 14:43:21 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_msh	g_msh;

/*
**	Minishell reads "minishell_history" text file at execution.
**	If the file doesn't exist, it creates it (check on errno)
*/

int	open_history_file(void)
{
	int	fd;

	fd = open(HISTORY_MSH, O_CREAT | O_RDWR | O_EXCL, S_IRUSR | S_IWUSR);
	if (fd < 0)
	{
		if (errno == EEXIST)
		{
			fd = open(HISTORY_MSH, O_RDWR, S_IRUSR | S_IWUSR);
		}
	}
	return (fd);
}

/*
**	Create the list of commands
*/

void	create_hist_list(t_hist *hist)
{
	int		res;
	char	*cmd;

	res = get_next_line(hist->fd, &cmd);
	while (res >= 0)
	{
		if (is_empty_str(cmd))
		{
			hist->history[hist->cursor] = ft_strdup(cmd);
			hist->cursor++;
			add_history(cmd);
		}
		free(cmd);
		cmd = NULL;
		if (res == 0)
			break ;
		res = get_next_line(hist->fd, &cmd);
	}
	if (cmd != NULL)
		free(cmd);
}

/*
**	Append the command to the history.
**	Consider the `hist.history` as a circular buffer, where the oldest
**	record will be overwrite by the use of cursor % HISTORY_MAX_SIZE.
*/

void	add_command_to_history(const char *command)
{
	unsigned int	index;

	if (is_empty_str(command) == 0 || *command == '\n' || *command == '\0')
		return ;
	index = (g_msh.hist.cursor % HISTORY_MAX_SIZE);
	if (g_msh.hist.history[index] != NULL)
		free(g_msh.hist.history[index]);
	g_msh.hist.history[index] = ft_strdup(command);
	if (g_msh.hist.history[index] == NULL)
		handle_error(ERR_MALLOC, MALLOC_FAILED);
	g_msh.hist.cursor++;
	g_msh.hist.cursor = (g_msh.hist.cursor % HISTORY_MAX_SIZE);
}

/*
**	write ~/.minishell_history file
*/

void	write_history_file(int fd)
{
	int	i;
	int	n;

	n = HISTORY_MAX_SIZE;
	i = g_msh.hist.cursor;
	while (n-- > 0)
	{
		if (g_msh.hist.history[i % HISTORY_MAX_SIZE] != NULL)
		{
			ft_putstr_fd(g_msh.hist.history[i % HISTORY_MAX_SIZE], fd);
			ft_putstr_fd("\n", fd);
			free(g_msh.hist.history[i % HISTORY_MAX_SIZE]);
			g_msh.hist.history[i % HISTORY_MAX_SIZE] = NULL;
		}
		i++;
	}
}

/*
**	 Exit function for history file
*/

void	update_history_file(void)
{
	int	fd;

	fd = open(HISTORY_MSH, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd < 0)
		printf("error: failed to update history file\n");
	write_history_file(fd);
	free(g_msh.hist.history);
	g_msh.hist.history = NULL;
	close(fd);
}
