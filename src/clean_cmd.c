/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 12:42:55 by rlinkov           #+#    #+#             */
/*   Updated: 2021/06/21 21:38:11 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_msh	g_msh;

void	join_split(char **strs, char *cleaned_cmd)
{
	int	i;
	int	j;
	int	pos;

	i = 0;
	pos = 0;
	while (strs[i] != 0)
	{
		j = 0;
		while (strs[i][j] != 0)
		{
			cleaned_cmd[pos + j] = strs[i][j];
			j++;
		}
		pos += j;
		i++;
	}
	cleaned_cmd[pos] = '\0';
}

char	*join_cmd(char **strs)
{
	int		len;
	int		i;
	char	*cleaned_cmd;

	i = 0;
	len = 0;
	while (strs[i] != 0)
	{
		len += ft_strlen(strs[i]);
		i++;
	}
	cleaned_cmd = (char *)malloc(sizeof(char *) * (len + 1));
	if (cleaned_cmd == NULL)
	{
		handle_error(ERR_MALLOC, MALLOC_FAILED);
		return (0);
	}
	join_split(strs, cleaned_cmd);
	return (cleaned_cmd);
}

char	*remove_char(char *full_cmd, int c)
{
	char	**strs;
	char	*clean_cmd;

	strs = ft_split(full_cmd, c);
	free(full_cmd);
	clean_cmd = join_cmd(strs);
	free_split(strs);
	return (clean_cmd);
}

char	*remove_space(char *full_cmd)
{
	char	**strs;
	char	*clean_cmd;
	int		i;

	i = 0;
	while (full_cmd[i] == SPACE_TOK)
		full_cmd[i++] = SPACERM;
	while (full_cmd[i] != 0)
	{
		if (full_cmd[i] == PIPE || full_cmd[i] == SEMICOLON)
		{
			i++;
			while (full_cmd[i] == SPACE_TOK && full_cmd[i])
				full_cmd[i++] = SPACERM;
		}
		else
			i++;
	}
	strs = ft_split(full_cmd, SPACERM);
	free(full_cmd);
	clean_cmd = join_cmd(strs);
	free_split(strs);
	return (clean_cmd);
}

/*
 **  fonction qui va nettoyer la commande de ses tokens
 */

char	*clean_cmd(char *full_cmd)
{
	full_cmd = remove_char(full_cmd, QUOTE);
	full_cmd = remove_char(full_cmd, DQUOTE);
	full_cmd = remove_char(full_cmd, BACKSLASH);
	return (full_cmd);
}
