/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlinkov <rlinkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 16:18:15 by rlinkov           #+#    #+#             */
/*   Updated: 2021/06/09 14:23:25 by rlinkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_msh g_msh;

/*
** Catch the signal sent by the user when CTRL + C is typed
*/

void	handle_ctrl_c(int signal)
{
	printf("\n");
	if (!g_msh.pid)
	{
		g_msh.status = 130;
		write(1, NEW_COMMAND_PROMPT, 32);
	}
	else
		kill(g_msh.pid, signal);
}

/*
** Catch the signal sent by the user when CTRL + \ is typed
*/

void	handle_ctrl_backslash(int signal)
{
	if (g_msh.pid)
	{
		kill(g_msh.pid, signal);
		g_msh.status = 131;
		ft_printf("\nQuit: %d\n", signal);
	}
}


/*
** Handle the signals call the appropriate function
*/

void    handle_signals(void)
{
    if (signal(SIGINT, &handle_ctrl_c) == SIG_ERR)
		ft_printf("Could not set SIGINT handler\n");
	if (signal(SIGQUIT, &handle_ctrl_backslash) == SIG_ERR)
		ft_printf("Could not set SIGQUIT handler\n");
}