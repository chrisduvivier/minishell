/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 17:07:07 by rlinkov           #+#    #+#             */
/*   Updated: 2021/06/10 23:53:31 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_msh	g_msh;

/*
 ** This function get the cmd passed to the msh and store it in full_cmd
 ** It also handle CTRL+D signal
 ** If the stdin is empty it calls exit
 ** Else it does nothing
 */

void	get_cmd(char **full_cmd)
{
	int		ret;
	char	temp[1];

	ret = get_next_line(0, full_cmd);
	if (ret == 0 && ft_strlen(*full_cmd) == 0)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		free(*full_cmd);
		free_env(g_msh.env);
		exit(EXIT_SUCCESS);
	}
	while (ret == 0)
	{
		ret = read(0, temp, 1);
	}
}	

/*
 **	Parse command string and fill data into a command table.
 */

t_cmd_table	fill_cmd_table(char *cmd)
{
	t_cmd_table	t_cmd;
	char		**tokens;
	int			j;

	j = 0;
	t_cmd_table_init(&t_cmd);
	tokens = ft_split(cmd, SPACE);
	while (tokens[j] != NULL)
		j++;
	t_cmd.argc = j;
	t_cmd.argv = ft_calloc(t_cmd.argc, sizeof(char *));
	if (!t_cmd.argv)
		handle_error(ERR_MALLOC, MALLOC_FAILED);
	j = 0;
	while (tokens[j] != NULL)
	{
		t_cmd.argv[j] = ft_strdup(tokens[j]);
		if (!t_cmd.argv[j])
			handle_error(ERR_MALLOC, MALLOC_FAILED);
		if (j == 0 && t_cmd.cmd == NULL)
			t_cmd.cmd = ft_strdup(tokens[0]);
		j++;
	}
	free_split(tokens);
	return (t_cmd);
}

/*
 **	Split commands by pipes, if any. Create command tables and fill them.
 **	@param:
 **		piped_command	whole cmd string potentially containing pipe
 */

t_cmd_table	*handle_pipes(char *piped_command)
{
	char		**single_cmds;
	int			len_cmds;
	t_cmd_table	*t_cmds;
	int			i;

	len_cmds = 0;
	single_cmds = ft_split(piped_command, PIPE);
	while (single_cmds[len_cmds] != NULL)
		len_cmds++;
	t_cmds = ft_calloc(len_cmds + 1, sizeof(t_cmd_table));
	if (t_cmds == NULL)
		handle_error(ERR_MALLOC, MALLOC_FAILED);
	i = 0;
	while (i < len_cmds)
	{
		t_cmds[i] = fill_cmd_table(single_cmds[i]);
		i++;
	}
	t_cmd_table_init(&t_cmds[i]);
	ft_split_free(single_cmds);
	set_pipes(t_cmds, len_cmds);
	check_redirections(t_cmds, len_cmds);
	g_msh.t_cmds = t_cmds;
	g_msh.t_cmds_len = len_cmds;
	return (t_cmds);
}

/*
 **	split the whole command (which has been cleaned/transform)
 **	1. Split based on the `;`
 **	2. Split based on the `|`
 **	into single executable command. (ex: [ls; cd ../] -> [[ls], [cd ../]])
 **
 **	if no pipe, only 1 basic_cmd
 */

void	split_command(char *full_cmd)
{
	char		**cmds;
	int			i;
	int			j;
	t_cmd_table	*t_cmd;

	i = 0;
	cmds = ft_split(full_cmd, SEMICOLON);
	free(full_cmd);
	g_msh.raw_cmds = cmds;
	g_msh.raw_cmds_len = ft_str_array_len((const char**)cmds);
	while (cmds[i] != NULL)
	{	
		t_cmd = handle_pipes(cmds[i]);
		free(cmds[i]);
		cmds[i] = NULL;
		j = 0;
		while (t_cmd[j].argc > 0 && t_cmd[j].argv[0] != NULL)
		{
			print_t_cmd_table(t_cmd[j]);
			exec_cmd(t_cmd[j]);
			j++;
		}
		i++;
		free(t_cmd);
	}
	free(cmds);
}

/*
 **	Prompt new line in shell
 **	
 */

void	prompt(void)
{
	char	*full_cmd;

	while (1)
	{
		ft_putstr_fd(NEW_COMMAND_PROMPT, STDOUT_FILENO);
		handle_signals();
		get_cmd(&full_cmd);
		full_cmd = code_cmd(full_cmd);
		full_cmd = remove_space(full_cmd);
		g_msh.status = 0;
		syntaxe_cmd(full_cmd);
		full_cmd = clean_cmd(full_cmd);
		if (g_msh.status == 0)
			split_command(full_cmd);
		else
			free(full_cmd);
	}
}
