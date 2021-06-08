/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 11:13:31 by cduvivie          #+#    #+#             */
/*   Updated: 2021/06/08 11:14:12 by cduvivie         ###   ########.fr       */
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
