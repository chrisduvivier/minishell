/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlinkov <rlinkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 13:25:32 by rlinkov           #+#    #+#             */
/*   Updated: 2021/06/09 16:43:47 by rlinkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_msh	g_msh;

void	handle_error(char *err_tag, int status)
{
	ft_putstr_fd(RED, 1);
	ft_putendl_fd(err_tag, 1);
	ft_putstr_fd(RESET, 1);
	g_msh.status = status;
	if (status == MALLOC_FAILED)
		exit(EXIT_FAILURE);
}
