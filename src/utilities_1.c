/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 11:13:31 by cduvivie          #+#    #+#             */
/*   Updated: 2021/06/25 19:09:43 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_msh	g_msh;

int	count_non_empty_arg(t_cmd_table *t_cmd)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (i < t_cmd->argc)
	{
		if (t_cmd->argv[i] && ft_strlen(t_cmd->argv[i]) > 0)
			count++;
		i++;
	}
	return (count);
}

/*
**  clean up t_cmd->argv and argc by removing empty argument.
**  @params:
**      *t_cmd: ptr to the command table
*/

void	clean_empty_arg(t_cmd_table *t_cmd)
{
	char	**new_argv;
	int		i;
	size_t	count;

	count = count_non_empty_arg(t_cmd);
	new_argv = (char **)ft_calloc(count + 1, sizeof(char *));
	if (!new_argv)
		handle_error(ERR_MALLOC, MALLOC_FAILED);
	i = 0;
	count = 0;
	while (i <= t_cmd->argc)
	{
		if (t_cmd->argv[i] && ft_strlen(t_cmd->argv[i]) > 0)
		{
			new_argv[count++] = ft_strdup(t_cmd->argv[i]);
		}
		free(t_cmd->argv[i]);
		i++;
	}
	new_argv[count] = NULL;
	free(t_cmd->argv);
	t_cmd->argv = new_argv;
	t_cmd->argc = count;
}

/*
 ** As the key of the environment variable can contain "_"
 ** ft_isalpha is not sufficient to check if the key is correct
 */

int	ft_isalpha_underscore(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_');
}

/*
 ** As the key of the environment variable can contain "_"
 ** ft_isalnum is not sufficient to check if the key is correct
 */

int	ft_isalnum_underscore(int c)
{
	return (ft_isdigit(c) || ft_isalpha_underscore(c));
}
