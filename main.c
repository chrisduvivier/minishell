/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 17:50:45 by rlinkov           #+#    #+#             */
/*   Updated: 2021/06/09 14:35:39 by rlinkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 **	declaration of the only global variable
 */

t_msh	g_msh;

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	t_msh_init();
	copy_env(envp);
	prompt();
	return (0);
}
