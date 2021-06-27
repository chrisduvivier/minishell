/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 16:18:15 by rlinkov           #+#    #+#             */
/*   Updated: 2021/06/27 01:28:46 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_msh	g_msh;

/*
**	Catch the signal sent by the user when CTRL + C is typed
**	Whenever signal detected in get_cmd, it clears the line and reset
**	its content.
*/

void	handle_ctrl_c(int signal)
{
	(void) signal;
	if (g_msh.heredoc != 1)
		printf("\n");
	g_msh.status = 130;
	if (g_msh.pid == 0)
	{
		rl_replace_line("", 0);
		rl_redisplay();
		ft_putstr_fd(NEW_COMMAND_PROMPT, STDOUT_FILENO);
	}
	else
		kill(g_msh.pid, SIGKILL);
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
