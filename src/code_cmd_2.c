/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code_cmd_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlinkov <rlinkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 17:25:03 by rlinkov           #+#    #+#             */
/*   Updated: 2021/06/09 18:35:56 by rlinkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_msh	g_msh;

/*
 ** This one not only subsitute $ token by an non printable char
 ** But is substitute $ token with the corresponding environment variable
 ** If it exist
 */

char	*handle_dollar(int *i, char *full_cmd, int *sq)
{
	if ((*sq % 2) == 0)
	{
		if (full_cmd[*i - 1] != BACKSLASH)
		{
			if (full_cmd[*i + 1] && full_cmd[*i + 1] != ' '
				&& full_cmd[*i + 1] != '=' && full_cmd[*i + 1] != ';')
			{
				full_cmd[*i] = DOLLAR;
				full_cmd = set_env_var(full_cmd, i);
			}
		}
	}
	return (full_cmd);
}

char	*handle_pipe(int *i, char *full_cmd, int *sq, int *dq)
{
	if ((*sq % 2) == 0 && (*dq % 2) == 0)
	{
		if (full_cmd[*i - 1] != BACKSLASH)
			full_cmd[*i] = PIPE;
	}
	return (full_cmd);
}

char	*handle_lchevron(int *i, char *full_cmd, int *sq, int *dq)
{
	if ((*sq % 2) == 0 && (*dq % 2) == 0)
	{
		if (full_cmd[*i - 1] != BACKSLASH)
			full_cmd[*i] = LCHEVRON;
	}
	return (full_cmd);
}

char	*handle_rchevron(int *i, char *full_cmd, int *sq, int *dq)
{
	if ((*sq % 2) == 0 && (*dq % 2) == 0)
	{
		if (full_cmd[*i - 1] != BACKSLASH)
			full_cmd[*i] = RCHEVRON;
	}
	return (full_cmd);
}

char	*handle_space(int *i, char *full_cmd, int *sq, int *dq)
{
	if ((*sq % 2) == 0 && (*dq % 2) == 0)
	{
		full_cmd[*i] = SPACE;
	}
	return (full_cmd);
}
