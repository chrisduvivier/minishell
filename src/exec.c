/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 17:01:52 by rlinkov           #+#    #+#             */
/*   Updated: 2021/06/11 00:55:12 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_msh	g_msh;

/*
**	Verify if the path given in cmd string is executable,
**	and copy the path cmd_abs_path.  
**	(ex: cmd="/bin/ls" -> verify with stat if OK to exec)
**	@params:
**		*t_cmd: ptr to the single command table 
*/

void	get_cmd_reltive_path(t_cmd_table *t_cmd)
{
	struct stat	buf;

	if (stat(t_cmd->cmd, &buf) == 0)
	{
		t_cmd->cmd_abs_path = ft_strdup(t_cmd->cmd);
	}
}

/*
**	concat and return complete path to the binary specified in cmd
**	@params:
**		path: path 
**		cmd: str of the name of the command
*/

char	*create_path_name(const char *path, const char *cmd)
{
	char	*tmp;
	char	*res;

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

/*
**	//TODO: malloc error
*/

void	set_cmd_abs_path(t_cmd_table *t_cmd)
{
	int			i;
	char		*path;
	char		**list_path;
	struct stat	buf;

	i = 0;
	if (t_cmd->cmd[0] == '.' || ft_strncmp(t_cmd->cmd, "./", 2) == 0)
		return (get_cmd_reltive_path(t_cmd));
	path = find_var("PATH");
	list_path = ft_split(path, ':');
	while (list_path[i] != NULL)
	{
		path = create_path_name(list_path[i], t_cmd->cmd);
		if (path == NULL)
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
**	@params:
**		t_cmd: the command table
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
**	Execute the command:
**		if matches one of our own builtin which needs to be executed without
**		child process, exec and return (ex: cd, export, unset exit)
**		otherwise, execute it in a child process.
**	@params:
**		t_cmd: the command table 
*/

/*
**		//TODO replace do while loop
*/

int	exec_cmd(t_cmd_table t_cmd)
{
	pid_t	pid;

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
	else
		exec_with_process(t_cmd);
	close_fd(t_cmd);
	free_t_cmd(&t_cmd);
	return (EXIT_SUCCESS);
}
