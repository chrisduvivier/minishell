/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 16:18:15 by rlinkov           #+#    #+#             */
/*   Updated: 2021/06/09 14:44:36 by cduvivie         ###   ########.fr       */
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
		ft_putstr_fd(NEW_COMMAND_PROMPT, STDOUT_FILENO);
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