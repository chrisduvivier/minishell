/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 17:07:07 by rlinkov           #+#    #+#             */
/*   Updated: 2021/05/31 15:24:11 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_msh g_msh;

void get_cmd(char **full_cmd)
{
	int ret;
	char temp[1];

	ret = get_next_line(0, full_cmd);
	if (ret == 0 && ft_strlen(*full_cmd) == 0) //check le CTRL + D
	{
		write(1, "exit\n", 6);
		free(*full_cmd);
		// free all malloced (msh)
		exit(EXIT_SUCCESS);
	}
	while (ret == 0)
	{
		ret = read(0, temp, 1);
	}
}

/*
**	Check for input output settings (>, <, >>)
*/

void	set_io(t_cmd_table *t_cmd)
{
	(void)t_cmd;
}

/*
**	Parse command string and fill data into a command table.
*/

t_cmd_table fill_cmd_table(char *cmd)
{
	t_cmd_table	t_cmd;
	char		**tokens;
	int			i;
	
	i = 0;
	t_cmd_table_init(&t_cmd); 
	tokens = ft_split(cmd, SPACE);
	free(cmd);
	while (tokens[i] != NULL)
		i++;
	t_cmd.argc = i;
	t_cmd.argv = ft_calloc(t_cmd.argc + 1, sizeof(char *));
	i = 0;
	while (tokens[i] != NULL)
	{
		t_cmd.argv[i] = ft_strdup(tokens[i]);
		//TODO MALLOC ERROR
		if (i == 0 && t_cmd.cmd == NULL)
			t_cmd.cmd = ft_strdup(tokens[0]);
		i++;
	}
	// Handle '>' and '<', '>>'
	set_io(&t_cmd);
	free(tokens);
	return (t_cmd);
}

/*
**	Iterate over piped commands and set their io fd.
**	@param:
**		t_cmds	table of single commands
**		t_size	size of the table (array of t_cmd)
*/

void	set_pipes(t_cmd_table *t_cmds, int t_size)
{
	(void)t_cmds;
	(void)t_size;
}

/*
**	Split commands by pipes, if any. Create command tables and fill them.
**	@param:
**		piped_command	whole cmd string potentially containing pipe
*/

t_cmd_table *handle_pipes(char *piped_command)
{
	char		**single_cmds;
	t_cmd_table	*t_cmds;
	int			i;

	i = 0;
	single_cmds = ft_split(piped_command, PIPE);
	free(piped_command);

	while (single_cmds[i] != NULL)
		i++;
	t_cmds = ft_calloc(i + 1, sizeof(t_cmd_table));
	if (t_cmds == NULL)
		return (NULL); //TODO MALLOC ERROR
	i = 0;
	while (single_cmds[i] != NULL)
	{
		t_cmds[i] = fill_cmd_table(single_cmds[i]);
		i++;
	}
	free(single_cmds);
	set_pipes(t_cmds, i);
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

void	split_command(char *full_cmd) //attention des free a rajouter (pour les splits et la cmd)
{
	char	**cmds;
	int		i;
	int		j;
	t_cmd_table *t_cmd;
	
	if (g_msh.status == 1)
	{
		i = 0;
		cmds = ft_split(full_cmd, SEMICOLON);
		free(full_cmd);
		while (cmds[i] != NULL)
		{	
			t_cmd = handle_pipes(cmds[i]);
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
	}
}

/*
**	Prompt new line in shell
**	
*/

void prompt(void)
{
	char *full_cmd;
	
	while (1)
	{
		write(1, NEW_COMMAND_PROMPT, 32);
		get_cmd(&full_cmd);
		// printf("COMMANDE RECUE : %s\n", full_cmd);
		full_cmd = code_cmd(full_cmd);
		// printf("COMMANDE CODEE : %s\n", full_cmd);
		full_cmd = remove_space(full_cmd);
		syntaxe_cmd(full_cmd);
		full_cmd = clean_cmd(full_cmd);
		// printf("COMMANDE CLEAN : %s\n\n", full_cmd);
		split_command(full_cmd);
		g_msh.status = 1;
	}
}