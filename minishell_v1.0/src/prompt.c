/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlinkov <rlinkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 17:07:07 by rlinkov           #+#    #+#             */
/*   Updated: 2021/04/30 17:16:36 by rlinkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_msh minishell;

void get_cmd(char **full_cmd)
{
	int ret;
	char temp[1];

	ret  = get_next_line(0, full_cmd);
	if (ret == 0 && ft_strlen(*full_cmd) == 0) //check le CTRL + D
	{
		write(1,"exit\n",6);
		free(*full_cmd);
		exit(EXIT_SUCCESS);
	}
	while (ret == 0)
	{
		ret = read(0, temp, 1);
	}
}

void parse_input(char *full_cmd) //attention des free a rajouter (pour les splits et la cmd)
{
	char **strs;
	int i;
	int j;
	char **basic_cmd;
	if (minishell.status == 1)
	{
		strs = ft_split_msh(full_cmd, SEMICOLON);
		i = 0;
		while (strs[i] != NULL)
		{
			j = 0;
			printf("---->COMMANDE [%d] : %s\n\n", i, strs[i]);
			basic_cmd = ft_split_msh(strs[i], PIPE);
			while (basic_cmd[j] !=0)
			{
				printf("------->BASIC CMD [%d] : %s\n\n", j, basic_cmd[j]);
				exec_cmd(basic_cmd[j]);
				j++;
			}
			i++;
		}
	}
}

void prompt()
{
	char *full_cmd;
	while (1)
	{
		write(1, "(╯°□°)╯︵ ┻━┻$> ", 32);
		get_cmd(&full_cmd);
		printf("COMMANDE RECUE : %s\n",full_cmd);
		code_cmd(full_cmd);
		printf("COMMANDE CODEE : %s\n",full_cmd);
		full_cmd = remove_space(full_cmd);
		syntaxe_cmd(full_cmd);
		full_cmd = clean_cmd(full_cmd);
		printf("COMMANDE CLEAN : %s\n\n",full_cmd);
		parse_input(full_cmd);
		minishell.status = 1;
	}
}