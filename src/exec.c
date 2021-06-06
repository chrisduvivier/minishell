/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 17:01:52 by rlinkov           #+#    #+#             */
/*   Updated: 2021/06/06 00:31:33 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_msh g_msh;

/*
**	close the fds that are piped
*/

void	close_fd(t_cmd_table t_cmd)
{
	if (t_cmd.in_file_fd != 0)
		close(t_cmd.in_file_fd);
	if (t_cmd.out_file_fd != 1)
		close(t_cmd.out_file_fd);
}

/*
** redirect the STDIN and STDOUT to the ones specified in t_cmd
*/

void	redirect_io(t_cmd_table t_cmd)
{
	if (t_cmd.in_file_fd != STDIN_FILENO)
		dup2(t_cmd.in_file_fd, STDIN_FILENO);
	if (t_cmd.out_file_fd != STDOUT_FILENO)
		dup2(t_cmd.out_file_fd, STDOUT_FILENO);
}

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

/*
**	Command executed on child process. Each function doesn't return value
*/

void	exec_with_process(t_cmd_table t_cmd)
{
	int		exec_res;

	redirect_io(t_cmd);
	if (is_our_builtin(t_cmd.cmd))
		return (builtin_caller_in_child(t_cmd));
	set_cmd_abs_path(&t_cmd);
	if (t_cmd.cmd_abs_path == NULL)
		exec_res = -1;
	else
		exec_res = execve(t_cmd.cmd_abs_path, t_cmd.argv, g_msh.env);
	if (exec_res < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(t_cmd.cmd, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit(127);
	}
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
	
	if (builtin_caller_in_parent(t_cmd))
	{
		free_t_cmd(&t_cmd);
		g_msh.pid = -1;
		return (EXIT_SUCCESS);
	}
	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("minishell: fork error\n", STDERR_FILENO);
		exit(127);
	}
	else if (pid > 0)
	{
		do
		{
			waitpid(pid, &g_msh.status, WUNTRACED);
		} while (!WIFEXITED(g_msh.status) && !WIFSIGNALED(g_msh.status));
	}
	else	//forked child process here
		exec_with_process(t_cmd);
	// parent process HERE
	close_fd(t_cmd);
	free_t_cmd(&t_cmd);
	return (EXIT_SUCCESS);
}
