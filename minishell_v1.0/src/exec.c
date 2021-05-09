/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 17:01:52 by rlinkov           #+#    #+#             */
/*   Updated: 2021/05/08 19:14:35 by cduvivie         ###   ########.fr       */
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
	builtin_function_caller(args);
	return (lsh_launch(args));
}

int exec_cmd(char *cmd) //sert juste d'exemple
{
	int i;
	char **args;

	printf("============== exec_cmd: [%s]=============\n", cmd);

	i = 0;
	args = ft_split_msh(cmd, SPACE);
	while (args[i] != NULL)
	{
		if (i == 0)
		{
			printf("----------->CMD[%i] : |%s|\n", i, args[i]);
			builtin_function_caller(args);
		}
		else
			printf("----------->ARG[%i] : |%s|\n", i, args[i]);
		i++;
	}
	return (lsh_launch(args));
	printf("\n");
}
