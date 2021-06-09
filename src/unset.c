/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlinkov <rlinkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 13:12:54 by rlinkov           #+#    #+#             */
/*   Updated: 2021/06/09 16:14:36 by rlinkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_msh	g_msh;

/*
 ** This function delete an entry from the environment array
 ** At the entry_pos passed
 */

void	delete_env_entry(int entry_pos)
{
	char	**new_env;
	int		env_size;
	int		i;
	int		j;

	env_size = 0;
	while (g_msh.env[env_size] != NULL)
		env_size++;
	new_env = malloc(sizeof(char *) * (env_size));
	if (!new_env)
		handle_error(ERR_MALLOC, MALLOC_FAILED);
	i = 0;
	j = 0;
	while (g_msh.env[j] != NULL)
	{
		if (j == env_size - 1)
			break ;
		if (j == entry_pos)
			j++;
		new_env[i++] = ft_strdup(g_msh.env[j++]);
	}
	new_env[i] = NULL;
	free_env(g_msh.env);
	g_msh.env = new_env;
}

/*
 ** This function find an existing environment variable position
 ** It returns the position found
 */

int	find_key_pos(char *key)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(key);
	while (g_msh.env[i] && g_msh.env[i] != NULL)
	{
		if (ft_strncmp(key, g_msh.env[i], len) == 0)
		{
			if (g_msh.env[i][len] && g_msh.env[i][len] == '=')
				return (i);
		}
		i++;
	}
	return (-1);
}

/*
 ** This function allow us to remove an environment variable from env
 */

void	msh_bi_unset(t_cmd_table t_cmd)
{
	int	key_pos;

	if (!ft_strcmp(t_cmd.argv[1], "_"))
		return ;
	if (is_key_valid(t_cmd.argv[1], (int)ft_strlen(t_cmd.argv[1])) == 0)
	{
		printf("msh: unset: `%s': not a valid identifier\n", t_cmd.argv[1]);
		return ;
	}
	if (!is_key_existing(t_cmd.argv[1]))
		return ;
	key_pos = find_key_pos(t_cmd.argv[1]);
	if (key_pos == -1)
		return ;
	delete_env_entry(key_pos);
}
