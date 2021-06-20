/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 12:25:36 by cduvivie          #+#    #+#             */
/*   Updated: 2021/06/20 11:37:57 by cduvivie         ###   ########.fr       */
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
**	Handles heredoc (<<) functionality of bash.
**	keep writing on STDINT until eof_string is given by user.
**	Doesn't not return by EOF signal. 
*/

void	exec_heredoc(t_cmd_table *t_cmd)
{
	int		ret;
	char	*user_input;

	heredoc_prompt(STDOUT_FILENO);
	ret = get_next_line(STDIN_FILENO, &user_input);
	while (ret >= 0 && user_input)
	{
		if (ret == 0 || ((ft_strlen(user_input) == ft_strlen(t_cmd->heredoc->eof_str))
            && (ft_strncmp(t_cmd->heredoc->eof_str, user_input, 
            ft_strlen(user_input)) == 0)))
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
	t_cmd->heredoc->tmp_file_fd = open(TMP_FILE_NAME, O_RDONLY);
	if (t_cmd->heredoc->tmp_file_fd < 0)
		printf("minishell: cannot read %s\n", TMP_FILE_NAME);
	dup2(t_cmd->heredoc->tmp_file_fd, t_cmd->in_file_fd);
	if (unlink(TMP_FILE_NAME) < 0)
		printf("error: unlink fail\n");
}