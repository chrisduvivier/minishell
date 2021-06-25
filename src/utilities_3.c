/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 19:06:37 by cduvivie          #+#    #+#             */
/*   Updated: 2021/06/25 19:39:21 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_msh	g_msh;

void	free_array_str(char **s, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(s[i]);
		s[i] = NULL;
		i++;
	}
}

void	fill_t_cmd_argv(t_cmd_table	*t_cmd, char **tokens)
{
	size_t	j;

	j = 0;
	while (tokens[j] != NULL)
	{
		t_cmd->argv[j] = ft_strdup(tokens[j]);
		if (!t_cmd->argv[j])
			handle_error(ERR_MALLOC, MALLOC_FAILED);
		if (j == 0 && t_cmd->cmd == NULL)
			t_cmd->cmd = ft_strdup(tokens[0]);
		j++;
	}
}
