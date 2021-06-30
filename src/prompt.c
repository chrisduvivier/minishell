/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 17:07:07 by rlinkov           #+#    #+#             */
/*   Updated: 2021/06/30 15:34:56 by cduvivie         ###   ########.fr       */
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
	*full_cmd = readline(NEW_COMMAND_PROMPT);
	if (*full_cmd == NULL)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		free(*full_cmd);
		free_msh_and_exit(EXIT_SUCCESS);
	}
	add_history(*full_cmd);
}

/*
 **	Parse command string and fill data into a command table.
 */

t_cmd_table	*fill_cmd_table(char *cmd)
{
	t_cmd_table	*t_cmd;
	char		**tokens;
	size_t		j;

	t_cmd = malloc(sizeof(t_cmd_table));
	if (!t_cmd)
		handle_error(ERR_MALLOC, MALLOC_FAILED);
	t_cmd_table_init(t_cmd);
	tokens = ft_split(cmd, SPACE_TOK);
	j = ft_str_array_len((const char **)tokens);
	t_cmd->argc = j;
	t_cmd->argv = (char **)ft_calloc(j + 1, sizeof(char *));
	if (!t_cmd->argv)
		handle_error(ERR_MALLOC, MALLOC_FAILED);
	fill_t_cmd_argv(t_cmd, tokens);
	free_split(tokens);
	return (t_cmd);
}

/*
 **	Split commands by pipes, if any. Create command tables and fill them.
 **	@param:
 **		piped_command	whole cmd string potentially containing pipe
 */

t_cmd_table	**handle_pipes(char *piped_command)
{
	char		**single_cmds;
	int			len_cmds;
	t_cmd_table	**t_cmds;
	int			i;

	single_cmds = ft_split(piped_command, PIPE);
	len_cmds = ft_str_array_len((const char **)single_cmds);
	t_cmds = (t_cmd_table **)ft_calloc(len_cmds + 1, sizeof(t_cmd_table *));
	g_msh.t_cmds = t_cmds;
	g_msh.t_cmds_len = len_cmds;
	if (t_cmds == NULL)
		handle_error(ERR_MALLOC, MALLOC_FAILED);
	i = 0;
	while (i < len_cmds)
	{
		t_cmds[i] = fill_cmd_table(single_cmds[i]);
		i++;
	}
	free_split(single_cmds);
	set_pipes(t_cmds, len_cmds);
	check_redirections(t_cmds, len_cmds);
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
	t_cmd_table	**t_cmds;

	cmds = ft_split(full_cmd, SEMICOLON);
	free(full_cmd);
	full_cmd = NULL;
	g_msh.raw_cmds = cmds;
	g_msh.raw_cmds_len = ft_str_array_len((const char **)cmds);
	t_cmds = NULL;
	i = 0;
	while (cmds[i] != NULL)
	{	
		t_cmds = handle_pipes(cmds[i]);
		j = 0;
		while (t_cmds[j] && t_cmds[j]->argc > 0 && t_cmds[j]->argv[0] != NULL)
			exec_cmd(t_cmds[j++]);
		free(t_cmds[j]);
		free(t_cmds);
		t_cmds = NULL;
		i++;
	}
	free_split(cmds);
	g_msh.pid = 0;
}

/*
 **	Prompt new line in shell.
 ** reset of status to 0 done after any insert of `echo $?`.
 */

void	prompt(void)
{
	char	*full_cmd;

	while (1)
	{
		handle_signals();
		get_cmd(&full_cmd);
		add_command_to_history(full_cmd);
		full_cmd = code_cmd(full_cmd);
		g_msh.status = 0;
		full_cmd = remove_space(full_cmd);
		syntaxe_cmd(full_cmd);
		full_cmd = clean_cmd(full_cmd);
		if (g_msh.status == SYNTAX_ERR)
		{
			free(full_cmd);
			continue ;
		}
		add_space_for_chevron(&full_cmd);
		split_command(full_cmd);
		g_msh.raw_cmds_len = 0;
		g_msh.raw_cmds = NULL;
		g_msh.t_cmds_len = 0;
		g_msh.t_cmds = NULL;
	}
}
