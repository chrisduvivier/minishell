/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_functions_helper.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 18:42:39 by cduvivie          #+#    #+#             */
/*   Updated: 2021/06/01 14:29:26 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Check whether the cmd name belongs to one of the function we coded ourself.
**	@param:
**		cmd		string containing command name
*/

int is_our_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

/*
**  Check if the command correspond to one of the builtin function, and exec.
**	Return Value:
**		1 is returned by each function upon success.
**		0 is returned when the cmd is not supported or error.
*/

int our_builtin_caller(t_cmd_table t_cmd)
{
	if (ft_strcmp(t_cmd.cmd, "echo") == 0)
		return (msh_echo(t_cmd));
	else if (ft_strcmp(t_cmd.cmd, "cd") == 0)
		return (msh_cd(t_cmd));
	else if (ft_strcmp(t_cmd.cmd, "pwd") == 0)
		return (msh_pwd(t_cmd));
	// else if (ft_strcmp(t_cmd.cmd, "export") == 0)
	// 	return (msh_export(t_cmd));
	// else if (ft_strcmp(t_cmd.cmd, "unset") == 0)
	// 	return (msh_unset(t_cmd));
	// else if (ft_strcmp(t_cmd.cmd, "env") == 0)
	// 	return (msh_env(t_cmd));
	else if (ft_strcmp(t_cmd.cmd, "exit") == 0)
		return (msh_exit(t_cmd));
	return (0);
}

/*
**  Check if the command requires to be run on a parent process
*/
int is_parent_cmd(char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);	
}
