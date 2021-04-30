/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlinkov <rlinkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 13:25:32 by rlinkov           #+#    #+#             */
/*   Updated: 2021/04/30 14:17:25 by rlinkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_msh minishell;

void	handle_error(char *err_tag)
{
	minishell.status = 0;
	ft_putstr_fd(RED, 1);
	ft_putendl_fd(err_tag, 1);
	ft_putstr_fd(RESET, 1);
	//exit(EXIT_FAILURE);
}