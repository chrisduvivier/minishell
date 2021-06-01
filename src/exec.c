/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 17:01:52 by rlinkov           #+#    #+#             */
/*   Updated: 2021/06/01 16:28:10 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_msh g_msh;

void	get_cmd_reltive_path(t_cmd_table *t_cmd)
{
	struct stat buf;

	if (stat(t_cmd->cmd, &buf) == 0)
	{
		t_cmd->cmd_abs_path = ft_strdup(t_cmd->cmd);
	}
}

/*
**	Take path string and command str to create a path to the binary
*/

char	*create_path_name(const char *path, const char *cmd)
{
	char *tmp;
	char *res;

	tmp = ft_strjoin(path, "/");
	if (tmp == NULL)
		return (NULL);
	res = ft_strjoin(tmp, cmd);
	free(tmp);
	return (res);
}

/*
**	Get the absolute path to the executable t_cmd->cmd
**	@params:
**		t_cmd : command table
**	@example:
**	"ls" -> "/bin/ls"
**	"../bin/ls" -> "../bin/ls" (no change if relative path is given)
*/

void	set_cmd_abs_path(t_cmd_table *t_cmd)
{
	int			i;
	char		*path;
	char		**list_path;
	struct stat buf;

	i = 0;
	if (t_cmd->cmd[0] == '.' || ft_strncmp(t_cmd->cmd, "./", 2) == 0)
		return (get_cmd_reltive_path(t_cmd));
	path = find_var("PATH");
	list_path = ft_split(path, ':');
	while (list_path[i] != NULL)
	{
		path = create_path_name(list_path[i], t_cmd->cmd);
		if (path == NULL)	//malloc error
			return ;
		if (stat(path, &buf) == 0)
		{
			ft_split_free(list_path);
			t_cmd->cmd_abs_path = path;
			return ;
		}
		free(path);
		i++;
	}
	ft_split_free(list_path);
}

int exec_with_process(t_cmd_table t_cmd)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		if (is_our_builtin(t_cmd.cmd))
			return (our_builtin_caller(t_cmd));
		else
		{
			set_cmd_abs_path(&t_cmd);
			if (t_cmd.cmd_abs_path == NULL)
			{
				perror("invalid path abs \n");
				return (-1);	//error
			}
			// printf("PATH=[%s]\n", t_cmd.cmd_abs_path);
			if (execve(t_cmd.cmd_abs_path, t_cmd.argv, g_msh.env) == -1)
			{
				perror("Could not execve");
			}
		}
	}
	else if (pid > 0)
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
	return (0);
}

// int lsh_launch(char **args)
// {
// 	pid_t pid;
// 	int status;

// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		if (execve(args[0], args, NULL) == -1)
// 			perror("Could not execve");
// 		return 1;

// 		exit(EXIT_FAILURE);
// 	}
// 	else if (pid < 0)
// 	{
// 		// Error forking
// 		perror("lsh");
// 	}
// 	else
// 	{
// 		// Parent process
// 		do
// 		{
// 			waitpid(pid, &status, WUNTRACED);
// 		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
// 	}
// 	return (1);
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
	// pid_t pid;
	
	// cmd requires no process 
	if (is_parent_cmd(t_cmd.cmd))
	{
		our_builtin_caller(t_cmd);
		free_t_cmd(&t_cmd);
		return (1);
	}
	return (exec_with_process(t_cmd));
}
