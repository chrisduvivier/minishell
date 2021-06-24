/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 13:25:32 by rlinkov           #+#    #+#             */
/*   Updated: 2021/06/24 00:05:12 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_msh	g_msh;

/*
**	Prints out error message and set the status of the error to the
**	global status variable. Only call exit in case of memory allocation error.
*/

void	handle_error(char *err_tag, int status)
{
	ft_putstr_fd(RED, 1);
	ft_putendl_fd(err_tag, 1);
	ft_putstr_fd(RESET, 1);
	g_msh.status = status;
	if (status == MALLOC_FAILED)
		exit(EXIT_FAILURE);
}
