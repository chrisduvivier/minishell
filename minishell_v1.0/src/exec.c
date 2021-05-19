/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 17:01:52 by rlinkov           #+#    #+#             */
/*   Updated: 2021/05/18 16:20:01 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_msh g_msh;

int lsh_launch(char **args)
{
	pid_t pid, wpid;
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
			wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (1);
}

int lsh_execute(char **args)
{
	if (args[0] == NULL)
	{
		// An empty command was entered.
		return (1);
	}
	builtin_caller(args);
	return (lsh_launch(args));
}

/*
**	Receieve a cleaned command line as string.
**	Execute the command:
**		if matches one of our own builtin, execute it (ex: echo, pwd, exit...)
**		otherwise, execute as native builtin function (ex: ls)
**	Input:
*/

int exec_cmd(char *cmd)
{
	char **args;

	args = ft_split(cmd, SPACE);
	// perhaps need to clean cmd
	if (is_builtin(cmd) == 1)
		return (builtin_caller(args));
	return (lsh_launch(args));
	printf("\n");
}
