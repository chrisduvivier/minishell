/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 12:25:36 by cduvivie          #+#    #+#             */
/*   Updated: 2021/06/26 23:55:48 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_msh	g_msh;

/*
**  Command prompted at beginning of each line of heredoc
*/

void	heredoc_prompt(int output_fd)
{
	ft_putstr_fd(HERE_DOC_PROMPT, output_fd);
}

/*
**	open the tmp file from beginning, and set the file descriptor of
**	t_cmd.
*/

void	exec_heredoc_helper(t_cmd_table *t_cmd)
{
	t_cmd->heredoc->tmp_file_fd = open(TMP_FILE_NAME, O_RDONLY);
	if (t_cmd->heredoc->tmp_file_fd < 0)
		printf("minishell: cannot read %s\n", TMP_FILE_NAME);
	dup2(t_cmd->heredoc->tmp_file_fd, t_cmd->in_file_fd);
	if (unlink(TMP_FILE_NAME) < 0)
		printf("error: unlink fail\n");
	g_msh.heredoc = 0;
}

/*
**	Handles heredoc (<<) functionality of bash.
**	keep writing on STDINT until eof_string is given by user.
**	Doesn't not return by EOF signal. 
*/

void	exec_heredoc(t_cmd_table *t_cmd)
{
	int		ret;
	size_t	len;
	char	*user_input;

	g_msh.heredoc = 1;
	heredoc_prompt(STDOUT_FILENO);
	ret = get_next_line(STDIN_FILENO, &user_input);
	while (ret >= 0 && user_input)
	{
		len = ft_strlen(user_input);
		if (ft_strlen(t_cmd->heredoc->eof_str) > len)
			len = ft_strlen(t_cmd->heredoc->eof_str);
		if (ret == 0 || !ft_strncmp(t_cmd->heredoc->eof_str, user_input, len))
			break ;
		ft_putstr_fd(user_input, t_cmd->heredoc->tmp_file_fd);
		ft_putstr_fd("\n", t_cmd->heredoc->tmp_file_fd);
		free(user_input);
		user_input = NULL;
		heredoc_prompt(STDOUT_FILENO);
		ret = get_next_line(STDIN_FILENO, &user_input);
	}
	free(user_input);
	ft_putstr_fd("\0", t_cmd->heredoc->tmp_file_fd);
	close(t_cmd->heredoc->tmp_file_fd);
	exec_heredoc_helper(t_cmd);
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
