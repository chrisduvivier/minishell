/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code_cmd_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 15:44:14 by cduvivie          #+#    #+#             */
/*   Updated: 2021/06/30 14:52:35 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_msh	g_msh;

int	find_space_pos_for_chevron(char *cmd, int len)
{
	int	i;

	i = 0;
	while (i < len - 1)
	{
		if (cmd[i] == LCHEVRON || cmd[i] == RCHEVRON)
		{
			if (cmd[i - 1] != SPACE_TOK && cmd[i - 1] != LCHEVRON
				&& cmd[i - 1] != RCHEVRON)
				return (i);
			if (cmd[i + 1] != SPACE_TOK && cmd[i + 1] != LCHEVRON
				&& cmd[i + 1] != RCHEVRON)
				return (i + 1);
		}
		i++;
	}
	return (-1);
}

char	*add_token_at_pos(char *str, int pos, char token)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = ft_calloc(ft_strlen(str) + 2, sizeof(char));
	if (!res)
		return (NULL);
	while (j < (int)(ft_strlen(str) + 1))
	{
		if (j == pos)
			res[j++] = token;
		else
			res[j++] = str[i++];
	}
	res[j] = '\0';
	return (res);
}

/*
 ** Add space token between CHEVRON TOKENS and other char
 */

void	add_space_for_chevron(char **cmd)
{
	char	*new_cmd;
	int		pos;

	pos = find_space_pos_for_chevron(*cmd, ft_strlen(*cmd));
	while (pos > 0)
	{
		new_cmd = add_token_at_pos(*cmd, pos, SPACE_TOK);
		free(*cmd);
		*cmd = new_cmd;
		pos = find_space_pos_for_chevron(*cmd, ft_strlen(*cmd));
	}
}
