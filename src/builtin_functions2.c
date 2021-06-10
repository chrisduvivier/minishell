/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_functions2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 01:00:48 by cduvivie          #+#    #+#             */
/*   Updated: 2021/06/11 02:18:29 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_msh	g_msh;

/*
**	Exit
**	@Description:
*/

void	msh_exit(t_cmd_table t_cmd)
{
	if (t_cmd.argc == 1)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		free_msh_and_exit(EXIT_SUCCESS);
	}
	else if (t_cmd.argc > 1)
	{
		if (ft_isdigit_string(t_cmd.argv[1]) == 1)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			if (t_cmd.argc == 2)
				free_msh_and_exit(ft_atoi(t_cmd.argv[1]));
			else
			{
				ft_printf("minishell: exit: too many arguments\n");
				g_msh.status = EXIT_FAILURE;
			}
		}
		else
		{
			ft_printf("minishell: exit: %s: numeric argument required\n",
				t_cmd.argv[1]);
			free_msh_and_exit(CMD_EXIT_ARG_FAILURE);
		}
	}
}

int	msh_export(t_cmd_table t_cmd)
{
	if (t_cmd.argv[1])
		msh_bi_export(t_cmd);
	return (1);
}

int	msh_unset(t_cmd_table t_cmd)
{
	if (t_cmd.argv[1])
		msh_bi_unset(t_cmd);
	return (1);
}

int	msh_env(t_cmd_table t_cmd)
{
	int	i;

	i = 0;
	(void) t_cmd;
	while (g_msh.env[i] != NULL)
	{
		printf("%s\n", g_msh.env[i]);
		i++;
	}
	return (1);
}
