/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 16:40:50 by cduvivie          #+#    #+#             */
/*   Updated: 2021/05/09 10:05:17 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Builtin function implementations.
*/

int msh_cd(char **args)
{
	
	// TODO: need to send the whole cmd+arg as string here.
	//		so far its sending none

	// if (chdir(args[1]) != 0)
	// {
	// 	perror("lsh");
	// }
	
	chdir(args[0]);
	return (1);
}

/*
**	psedocode for echo:
**	no specific return value expected
*/

int msh_echo(char **args)
{
	(void)args;
	// check if any arguments are given
		// return if none
	// check if first argument after echo is an option
		// if so, no \n at the end
	// while args[i], write to *OUTPUT_FILE (fd, str, ft_strlen(str))
	return (1);
}

/*
**	psedocode for pwd:
**	pwd - print name of current/working directory
**
**	Description:
**		getcwd is called just to get the pointer to the path string.
*/

int msh_pwd(char **args)
{	
	char	*ptr;
	int		fd;


	(void)args;
	//TODO get the appropriate fd
	// should be able to support ex: pwd > pwd.txt 
	fd = STDOUT_FILENO;
	ptr = NULL;	
	getcwd(ptr, 0);
	ft_putstr_fd(ptr, fd);
	ft_putchar_fd('\n', fd);
	return (1);
}

/*
**	
**	TODO:
**		- call free_anc_exit function 
*/

int msh_exit(char **args)
{
	(void)args;
	exit(0);
	return (0);
}
