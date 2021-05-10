/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 17:01:52 by rlinkov           #+#    #+#             */
/*   Updated: 2021/05/10 18:41:50 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int lsh_launch(char **args)
{
	pid_t pid, wpid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		// Child process
		if (execvp(args[0], args) == -1)
		{
			perror("lsh");
		}
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

int exec_cmd(t_msh *msh, char *cmd)
{
	char **args;

	(void)msh;
	args = ft_split_msh(cmd, SPACE);
	if (is_builtin(cmd) == 1)
		return (builtin_caller(args));
	return (lsh_launch(args));
	printf("\n");
}
