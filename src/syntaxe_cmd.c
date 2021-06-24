/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:13:41 by rlinkov           #+#    #+#             */
/*   Updated: 2021/06/24 12:53:58 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_msh	g_msh;

int	next_to_chevron_bis(char *full_cmd, int i, int start_i)
{
	if (full_cmd[start_i] == LCHEVRON && full_cmd[start_i + 1] == LCHEVRON
		&& full_cmd[start_i + 2] == LCHEVRON)
		return (3);
	if (full_cmd[start_i] == RCHEVRON && full_cmd[i] == LCHEVRON)
		return (3);
	if (full_cmd[start_i] == LCHEVRON && full_cmd[i] == RCHEVRON
		&& full_cmd[i + 1] == RCHEVRON)
		return (5);
	if (full_cmd[start_i] == LCHEVRON && full_cmd[i] == RCHEVRON
		&& full_cmd[i + 1] != RCHEVRON)
		return (4);
	return (0);
}

int	next_to_chevron(char *full_cmd, int i)
{
	int	start_i;

	start_i = i;
	i++;
	if (!full_cmd[i])
		return (1);
	if (full_cmd[i] == RCHEVRON && full_cmd[i - 1] == RCHEVRON
		&& full_cmd[i + 1] == RCHEVRON)
		return (5);
	while (full_cmd[i] == SPACE_TOK || full_cmd[i] == SEMICOLON)
		i++;
	if (full_cmd[i - 1] == SPACE_TOK && !full_cmd[i])
		return (1);
	if (full_cmd[i - 1] == SEMICOLON && !full_cmd[i])
		return (2);
	if (next_to_chevron_bis(full_cmd, i, start_i))
		return (next_to_chevron_bis(full_cmd, i, start_i));
	return (0);
}

void	check_part_two(char *full_cmd, int i)
{
	if (full_cmd[i] == LCHEVRON || full_cmd[i] == RCHEVRON)
	{
		if (next_to_chevron(full_cmd, i) == 1)
			handle_error(ERR_PARS_NL, SYNTAX_ERR);
		else if (next_to_chevron(full_cmd, i) == 2)
			handle_error(ERR_PARS_SEMI, SYNTAX_ERR);
		else if (next_to_chevron(full_cmd, i) == 3)
			handle_error(ERR_PARS_LC, SYNTAX_ERR);
		else if (next_to_chevron(full_cmd, i) == 4)
			handle_error(ERR_PARS_RC, SYNTAX_ERR);
		else if (next_to_chevron(full_cmd, i) == 5)
			handle_error(ERR_PARS_RRC, SYNTAX_ERR);
	}
}

void	check_part_one(char *full_cmd, int i, int *sq, int *dq)
{
	if (full_cmd[i] == QUOTE)
		*sq = *sq + 1;
	if (full_cmd[i] == DQUOTE)
		*dq = *dq + 1;
	if (full_cmd[i] == PIPE)
	{
		if (full_cmd[i + 1] != 0 && full_cmd[i + 1] == PIPE)
			handle_error(ERR_PARS_PIPE, SYNTAX_ERR);
		if (full_cmd[i + 1] == 0)
			handle_error(ERR_MULTILINE, SYNTAX_ERR);
		if (full_cmd[i - 1] == SEMICOLON)
			handle_error(ERR_PARS_PIPE, SYNTAX_ERR);
	}
	if (full_cmd[i] == SEMICOLON)
	{
		if (full_cmd[i + 1] != 0 && full_cmd[i + 1] == SEMICOLON)
			handle_error(ERR_PARS_SEMI, SYNTAX_ERR);
	}
}

void	syntaxe_cmd(char *full_cmd)
{
	int	sq;
	int	dq;
	int	i;

	i = 0;
	sq = 0;
	dq = 0;
	if (i == 0)
	{
		if (full_cmd[i] == PIPE)
			handle_error(ERR_PARS_PIPE, SYNTAX_ERR);
		else if (full_cmd[i] == SEMICOLON)
			handle_error(ERR_PARS_SEMI, SYNTAX_ERR);
	}
	while (full_cmd[i] != 0 && g_msh.status == 0)
	{
		check_part_one(full_cmd, i, &sq, &dq);
		check_part_two(full_cmd, i);
		i++;
	}
	if ((sq % 2) != 0 || (dq % 2) != 0)
		handle_error(ERR_MULTILINE, SYNTAX_ERR);
}
