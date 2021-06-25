/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_functions_helper.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 18:42:39 by cduvivie          #+#    #+#             */
/*   Updated: 2021/06/24 21:57:12 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Check whether the cmd name belongs to one of the function we coded ourself.
**	@param:
**		cmd		string containing command name
*/

int	is_our_builtin(char *cmd)
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

int	builtin_caller_in_parent(t_cmd_table *t_cmd)
{
	if (ft_strcmp(t_cmd->cmd, "cd") == 0)
		return (msh_cd(*t_cmd));
	else if (ft_strcmp(t_cmd->cmd, "export") == 0)
		return (msh_export(*t_cmd));
	else if (ft_strcmp(t_cmd->cmd, "unset") == 0)
		return (msh_unset(*t_cmd));
	else if (ft_strcmp(t_cmd->cmd, "exit") == 0)
	{
		msh_exit(*t_cmd);
		return (1);
	}
	return (0);
}

/*
**	builtins which have to be called in child process
*/

void	builtin_caller_in_child(t_cmd_table *t_cmd)
{
	if (ft_strcmp(t_cmd->cmd, "echo") == 0)
		msh_echo(*t_cmd);
	else if (ft_strcmp(t_cmd->cmd, "pwd") == 0)
		msh_pwd(*t_cmd);
	else if (ft_strcmp(t_cmd->cmd, "env") == 0)
		msh_env(*t_cmd);
	free_t_cmd(t_cmd);
	exit(EXIT_SUCCESS);
}
