/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 16:40:50 by cduvivie          #+#    #+#             */
/*   Updated: 2021/06/02 15:27:54 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_msh g_msh;

/*
**	Builtin function implementations.
**	@param:
**		t_cmd the table with command input
*/

int msh_cd(t_cmd_table t_cmd)
{
	(void)t_cmd;
	char *path;

	if (t_cmd.argc == 1)
	{
		path = find_var("HOME");
		chdir(path);
		free(path);
		// TODO set OK status
	}
	else if (t_cmd.argc > 2)
	{
		ft_printf("cd: too many arguments\n");
		// TODO set ERROR status
		return (0);
	}
	else if (chdir(t_cmd.argv[1]) < 0)
	{
		ft_printf("cd: no such file or directory: %s\n", t_cmd.argv[1]);
		// TODO set ERROR status
		return (0);
	}
	return (1);
}

/*
**	echo
*/

void	msh_echo(t_cmd_table t_cmd)
{
	int i;
	// int j;

	i = 0;
	if (t_cmd.argc > 1)
	{
		// support -n option
		i = 1;
		while (t_cmd.argv[i] != NULL)
		{
			ft_printf(t_cmd.argv[i]);
			i++;
			if (i < t_cmd.argc)
				ft_printf(" ");
		}
		ft_printf("\n");
	}
	else
		ft_printf("\n");
}

/*
**	psedocode for pwd:
**	pwd - print name of current/working directory
**
**	Description:
**		getcwd is called just to get the pointer to the path string.
*/

int msh_pwd(t_cmd_table t_cmd)
{	
	char	*ptr;

	// TODO should be able to support ex: pwd > pwd.txt 
	ptr = NULL;
	ptr = getcwd(ptr, 0);
	ft_putstr_fd(ptr, t_cmd.out_file_fd);
	ft_putchar_fd('\n', t_cmd.out_file_fd);
	return (1);
}

/*
**	
**	TODO:
**		- call free_anc_exit function 
*/

int msh_exit(t_cmd_table t_cmd)
{
	(void)t_cmd;
	return (1);
}

int 	msh_export(t_cmd_table t_cmd)
{
	(void)t_cmd;
	return (1);
}

int 	msh_unset(t_cmd_table t_cmd)
{
	(void)t_cmd;
	return (1);
}

int 	msh_env(t_cmd_table t_cmd)
{
	(void)t_cmd;
	return (1);
}
