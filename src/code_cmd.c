/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 14:13:53 by rlinkov           #+#    #+#             */
/*   Updated: 2021/06/25 02:06:37 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_msh	g_msh;

int	is_token(char c)
{
	if (c == '\\')
		return (BACKSLASH);
	else if (c == '\'')
		return (QUOTE);
	else if (c == '"')
		return (DQUOTE);
	else if (c == ';')
		return (SEMICOLON);
	else if (c == '$')
		return (DOLLAR);
	else if (c == '|')
		return (PIPE);
	else if (c == '<')
		return (LCHEVRON);
	else if (c == '>')
		return (RCHEVRON);
	else if (c == ' ')
		return (SPACE_TOK);
	return (0);
}

char	*check_token_in_cmd(int *i, char *full_cmd, int *sq, int *dq)
{
	int	token;

	token = is_token(full_cmd[*i]);
	if (token == BACKSLASH)
		full_cmd = handle_backslash(i, full_cmd, sq, dq);
	else if (token == QUOTE)
		full_cmd = handle_quote(i, full_cmd, sq, dq);
	else if (token == DQUOTE)
		full_cmd = handle_dquote(i, full_cmd, sq, dq);
	else if (token == SEMICOLON)
		full_cmd = handle_semicolon(i, full_cmd, sq, dq);
	else if (token == DOLLAR)
		full_cmd = handle_dollar(i, full_cmd, sq);
	else if (token == PIPE)
		full_cmd = handle_pipe(i, full_cmd, sq, dq);
	else if (token == LCHEVRON)
		full_cmd = handle_lchevron(i, full_cmd, sq, dq);
	else if (token == RCHEVRON)
		full_cmd = handle_rchevron(i, full_cmd, sq, dq);
	else if (token == SPACE_TOK)
		full_cmd = handle_space(i, full_cmd, sq, dq);
	return (full_cmd);
}

char	*check_token(int *i, char *full_cmd, int *sq, int *dq)
{
	int	token;

	token = is_token(full_cmd[*i]);
	if (*i == 0)
	{
		full_cmd[*i] = token;
		if (token == QUOTE)
			*sq = *sq + 1;
		else if (token == DQUOTE)
			*dq = *dq + 1;
		else if (token == DOLLAR
			&& (full_cmd[*i + 1] != ' ' && full_cmd[*i + 1] != '='
				&& full_cmd[*i + 1] != ';' && full_cmd[*i + 1]))
			full_cmd = set_env_var(full_cmd, i);
		else if (token == DOLLAR
			&& (full_cmd[*i + 1] == ' ' || full_cmd[*i + 1] == '='
				|| full_cmd[*i + 1] == ';' || !full_cmd[*i + 1]))
			full_cmd[*i] = '$';
	}
	else
		full_cmd = check_token_in_cmd(i, full_cmd, sq, dq);
	return (full_cmd);
}

char	*code_cmd(char *full_cmd)
{
	int	i;
	int	simple_quote;
	int	double_quote;

	i = 0;
	simple_quote = 0;
	double_quote = 0;
	while (full_cmd[i])
	{
		if (is_token(full_cmd[i]) != 0)
			full_cmd = check_token(&i, full_cmd, &simple_quote, &double_quote);
		i++;
	}
	return (full_cmd);
}
