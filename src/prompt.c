/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 17:07:07 by rlinkov           #+#    #+#             */
/*   Updated: 2021/05/31 01:05:40 by cduvivie         ###   ########.fr       */
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
**	Parse command stringa and fill data into a command table.
*/

t_cmd_table fill_cmd_table(char cmd)
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
		t_cmd.cmd = ft_strdup(tokens[i]);
		if (t_cmd.cmd == NULL)
			return ;	//TODO MALLOC ERROR
	}
	free(tokens);
	return (t_cmd);
}

/*
**	Split commands by pipes, if any.
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
	set_io(t_cmds, i);
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
	char	**basic_cmd;
	int		i;
	int		j;
	t_cmd_table *t_cmd;
	
	if (g_msh.status == 1)
	{
		cmds = ft_split(full_cmd, SEMICOLON);
		free(full_cmd);
		i = 0;
		while (cmds[i] != NULL)
		{
			j = 0;
			
			
			// basic_cmd = ft_split(cmds[i], PIPE);	//set back this to revert current WIP change
			
			t_cmd = handle_pipes(cmds[i]);			//comment  this to revert current WIP change
			
			
			while (basic_cmd[j] != 0)
			{
				// printf("------->BASIC CMD [%d] : %s\n\n", j, basic_cmd[j]);
				exec_cmd(basic_cmd[j]);
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