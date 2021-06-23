/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 16:18:15 by rlinkov           #+#    #+#             */
/*   Updated: 2021/06/23 21:25:00 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_msh	g_msh;

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
	{
		g_msh.status = 130;
		kill(g_msh.pid, signal);
	}
}

/*
** Catch the signal sent by the user when CTRL + \ is typed
*/

void	handle_ctrl_backslash(int signal)
{
	if (g_msh.pid)
	{
		g_msh.status = 131;
		kill(g_msh.pid, signal);
		printf("Quit\n");
	}
}

/*
** Handle the signals call the appropriate function
*/

void	handle_signals(void)
{
	if (signal(SIGINT, &handle_ctrl_c) == SIG_ERR)
		printf("Could not set SIGINT handler\n");
	if (signal(SIGQUIT, &handle_ctrl_backslash) == SIG_ERR)
		printf("Could not set SIGQUIT handler\n");
}
