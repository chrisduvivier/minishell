/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 15:17:26 by cduvivie          #+#    #+#             */
/*   Updated: 2021/06/06 00:13:44 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_msh g_msh;

void	color_set_red(void)
{
	ft_printf("\033[2;31m");
}

void	color_set_yellow(void)
{
	ft_printf("\033[2;33m");
}

void	color_reset(void)
{
	ft_printf("\033[0m");
}

void print_t_cmd_table(t_cmd_table t_cmd)
{
	int i;

	i = 0;
	color_set_yellow();
	ft_printf("========== DEBUG:print_t_cmd_table ==========\n");
	// ft_printf("g_msh.pid	:[%d]\n", g_msh.pid);
	if (t_cmd.cmd)
		ft_printf("cmd			:[%s]\n", t_cmd.cmd);
	if (t_cmd.argc)
		ft_printf("argc			:[%d]\n", t_cmd.argc);
	while (i < t_cmd.argc)
	{
		if (t_cmd.argv && t_cmd.argv[i])
			ft_printf("argv[%d]			:[%s]\n", i, t_cmd.argv[i]);
		i++;
	}
	ft_printf("input fd		:[%d]\n", t_cmd.in_file_fd);
	ft_printf("output fd		:[%d]\n", t_cmd.out_file_fd);
	ft_printf("=============================================\n");
	color_reset();
}