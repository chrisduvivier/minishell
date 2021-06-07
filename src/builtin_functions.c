/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlinkov <rlinkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 16:40:50 by cduvivie          #+#    #+#             */
/*   Updated: 2021/06/07 17:54:39 by rlinkov          ###   ########.fr       */
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
**	echo function
**	@option -n supported: no EOL if -n is given and num of arg > 2
*/

/*
**	check if option -n is valid.
**	Return 1 (true) if we can print \n;
*/

int		check_echo_option(t_cmd_table t_cmd)
{
	int new_line;
	
	new_line = 1;
	if (ft_strncmp(t_cmd.argv[1], "-n", ft_strlen(t_cmd.argv[1])) && t_cmd.argc > 2)
	{
		new_line = 0;
	}
	return (new_line);
}

void	msh_echo(t_cmd_table t_cmd)
{
	int i;
	int new_line;

	i = 1;
	new_line = 1;
	if (t_cmd.argc == 1)
	{
		ft_printf("\n");
		return ;
	}
	if (!ft_strncmp(t_cmd.argv[1], "-n", ft_strlen(t_cmd.argv[1])))
	{
		i++;
		new_line = 0;
	}
	while (t_cmd.argv[i] != NULL)
	{
		ft_printf(t_cmd.argv[i++]);
		if (i < t_cmd.argc)
			ft_printf(" ");
	}
	if (new_line == 1)
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
	if (t_cmd.argv[1])
		msh_bi_export(t_cmd);
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
	int i;
	
	i = 0;
	while(g_msh.env[i] != NULL)
	{
		printf("%s\n", g_msh.env[i]);
		i++;
	}
	return (1);
}
