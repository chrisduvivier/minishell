/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 13:25:32 by rlinkov           #+#    #+#             */
/*   Updated: 2021/05/18 15:48:03 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_msh g_msh;

void	handle_error(char *err_tag)
{
	ft_putstr_fd(RED, 1);
	ft_putendl_fd(err_tag, 1);
	ft_putstr_fd(RESET, 1);
	g_msh.status = 0;
	//exit(EXIT_FAILURE);
}