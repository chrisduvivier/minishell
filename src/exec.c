/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 17:01:52 by rlinkov           #+#    #+#             */
/*   Updated: 2021/05/31 15:15:10 by cduvivie         ###   ########.fr       */
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

/*
**	Receieve a command table t_cmd
**	Execute the command:
**		if matches one of our own builtin, execute it (ex: echo, pwd, exit...)
**		otherwise, execute as native builtin function (ex: ls)
**	Input:
*/

int exec_cmd(t_cmd_table t_cmd)
{
	if (is_our_builtin(t_cmd.cmd) == 1)
		return (our_builtin_caller(t_cmd));
	return (lsh_launch(t_cmd.argv));
	printf("\n");
}
