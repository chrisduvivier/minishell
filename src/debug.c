/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 15:17:26 by cduvivie          #+#    #+#             */
/*   Updated: 2021/06/26 23:49:46 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_msh	g_msh;

void	color_set_red(void)
{
	printf("\033[2;31m");
}

void	color_set_yellow(void)
{
	printf("\033[2;33m");
}

void	color_reset(void)
{
	printf("\033[0m");
}

void	print_list_t_cmd_table(t_cmd_table **t_cmds)
{
	int	i;

	i = 0;
	printf("############## DEBUG:print_list_t_cmd_table ###############\n");
	while (t_cmds[i])
	{
		print_t_cmd_table(t_cmds[i]);
		i++;
	}
	printf("###########################################################\n");
}

void	print_t_cmd_table(t_cmd_table *t_cmd)
{
	int	i;

	i = 0;
	color_set_yellow();
	printf("========== DEBUG:print_t_cmd_table ==========\n");
	printf("cmd			:[%s]\n", t_cmd->cmd);
	printf("cmd			:[NULL]\n");
	printf("cmd_abs_path		:[%s]\n", t_cmd->cmd_abs_path);
	printf("argc			:[%d]\n", t_cmd->argc);
	while (i < t_cmd->argc)
	{
		if (t_cmd->argv && t_cmd->argv[i])
			printf("argv[%d]			:[%s]\n", i, t_cmd->argv[i]);
		else
			printf("argv[%d]			:[NULL]\n", i);
		i++;
	}
	printf("input fd		:[%d]\n", t_cmd->in_file_fd);
	printf("output fd		:[%d]\n", t_cmd->out_file_fd);
	printf("g_msh status		:[%d]\n", g_msh.status);
	printf("=============================================\n");
	color_reset();
}
