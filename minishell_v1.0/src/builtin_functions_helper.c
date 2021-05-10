/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_functions_helper.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 18:42:39 by cduvivie          #+#    #+#             */
/*   Updated: 2021/05/09 19:00:24 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_builtin(char *cmd)
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
**		0 is returned when the cmd is not supported.
*/

int builtin_caller(char **args)
{
	char *cmd;

	cmd = args[0];
	if (ft_strcmp(cmd, "echo") == 0)
		return (msh_echo(args));
	else if (ft_strcmp(cmd, "cd") == 0)
		return (msh_cd(args));
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (msh_pwd(args));
	// else if (ft_strcmp(cmd, "export") == 0)
	// 	return (msh_export(args));
	// else if (ft_strcmp(cmd, "unset") == 0)
	// 	return (msh_unset(args));
	// else if (ft_strcmp(cmd, "env") == 0)
	// 	return (msh_env(args));
	else if (ft_strcmp(cmd, "exit") == 0)
		return (msh_exit(args));
	return (0);
}
