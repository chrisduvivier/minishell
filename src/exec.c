/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 17:01:52 by rlinkov           #+#    #+#             */
/*   Updated: 2021/06/01 14:36:52 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_msh g_msh;

int lsh_launch(char **args)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(args[0], args, NULL) == -1)
			perror("Could not execve");
		return 1;

		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		// Error forking
		perror("lsh");
	}
	else
	{
		// Parent process
		do
		{
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (1);
}

// int lsh_execute(char **args)
// {
// 	if (args[0] == NULL)
// 	{
// 		// An empty command was entered.
// 		return (1);
// 	}
// 	builtin_caller(args);
// 	return (lsh_launch(args));
// }

int	is_parent_process(int pid)
{
	return (pid > 0);
}

int	is_child_process(int pid)
{
	return (pid == 0);
}

/*
**	Receieve a command table t_cmd
**	Execute the command:
**		if matches one of our own builtin, execute it (ex: echo, pwd, exit...)
**		otherwise, execute as native builtin function (ex: ls)
**	Input:
*/

int exec_cmd(t_cmd_table t_cmd)
{
	pid_t pid;
	
	// cmd requires to be exec on parent process
	if (is_parent_cmd(t_cmd.cmd))
	{
		our_builtin_caller(t_cmd);
		free_t_cmd(&t_cmd);
		return (1);
	}
	// cmd is our builtin child process or else
	
	pid = fork();
	if (is_child_process(pid))
	{
		if (is_our_builtin(t_cmd.cmd))
		{
			our_builtin_caller(t_cmd);
		}
		else
		{
			if (execve(t_cmd.cmd_abs_path, t_cmd.argv, g_msh.env) == -1)
			{
				perror("Could not execve");
			}
		}
	}
	else if (is_parent_process(pid))
	{
		do
		{
			waitpid(pid, &g_msh.status, WUNTRACED);
		} while (!WIFEXITED(g_msh.status) && !WIFSIGNALED(g_msh.status));
	}
	else
	{
		// fork error
		perror("fork error");
		exit(0);
	}
	return (1);
}
