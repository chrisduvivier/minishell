/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code_cmd_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlinkov <rlinkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 17:26:03 by rlinkov           #+#    #+#             */
/*   Updated: 2021/06/09 18:36:56 by rlinkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_msh	g_msh;

char	*handle_backslash(int *i, char *full_cmd, int *sq, int *dq)
{
	if (full_cmd[*i - 1] != BACKSLASH)
	{
		if ((*sq % 2) == 0)
		{
			if ((*dq % 2) == 0)
			{
				full_cmd[*i] = BACKSLASH;
			}
			else if (full_cmd[*i + 1] != 0)
			{
				if (full_cmd[*i + 1] == '$' || full_cmd[*i + 1] == '"')
					full_cmd[*i] = BACKSLASH;
			}
		}
	}
	return (full_cmd);
}

char	*handle_quote(int *i, char *full_cmd, int *sq, int *dq)
{
	if ((*dq % 2) == 0)
	{
		if (full_cmd[*i - 1] != BACKSLASH)
		{
			full_cmd[*i] = QUOTE;
			*sq = *sq + 1;
		}
	}
	return (full_cmd);
}

char	*handle_dquote(int *i, char *full_cmd, int *sq, int *dq)
{
	if ((*sq % 2) == 0)
	{
		if (full_cmd[*i - 1] != BACKSLASH)
		{
			full_cmd[*i] = DQUOTE;
			*dq = *dq + 1;
		}
	}
	return (full_cmd);
}

char	*handle_semicolon(int *i, char *full_cmd, int *sq, int *dq)
{
	if ((*sq % 2) == 0 && (*dq % 2) == 0)
	{
		if (full_cmd[*i - 1] != BACKSLASH)
			full_cmd[*i] = SEMICOLON;
	}
	return (full_cmd);
}
