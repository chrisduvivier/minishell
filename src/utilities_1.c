/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlinkov <rlinkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 11:13:31 by cduvivie          #+#    #+#             */
/*   Updated: 2021/06/09 17:16:44 by rlinkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_msh g_msh;

/*
**  clean up t_cmd->argv and argc by removing empty argument.
**  @params:
**      *t_cmd: ptr to the command table
*/

void	clean_empty_arg(t_cmd_table *t_cmd)
{
	char	**new_argv;
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (i < t_cmd->argc)
	{
		if (t_cmd->argv[i][0] != '\0')
			count++;
		i++;
	}
	new_argv = (char **)ft_calloc(count + 1, sizeof(char *));
	if (!new_argv)
		exit(1);    //TODO
	i = 0;
	count = 0;
	while (i < t_cmd->argc)
	{
		if (t_cmd->argv[i] != NULL && t_cmd->argv[i][0] != '\0')
			new_argv[count++] = ft_strdup(t_cmd->argv[i]);
		free(t_cmd->argv[i++]);
	}
	new_argv[count] = NULL;
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
