/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 13:25:32 by rlinkov           #+#    #+#             */
/*   Updated: 2021/05/08 19:24:26 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_error(t_msh *msh, char *err_tag)
{
	ft_putstr_fd(RED, 1);
	ft_putendl_fd(err_tag, 1);
	ft_putstr_fd(RESET, 1);
	msh->status = 0;
	//exit(EXIT_FAILURE);
}