/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_functions_helper.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 18:42:39 by cduvivie          #+#    #+#             */
/*   Updated: 2021/05/08 19:14:05 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**  Check if the command correspond to one of the builtin function, and exec.
*/

int builtin_function_caller(char **args)
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
