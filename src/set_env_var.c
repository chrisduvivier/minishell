/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 15:27:33 by rlinkov           #+#    #+#             */
/*   Updated: 2021/06/25 14:20:51 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_msh	g_msh;

void	set_space(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == ' ')
			str[i] = SPACE_TOK;
		i++;
	}
}

/*
 ** Find the corresponding environment variable and return it
 */

char	*find_var(char *var_name)
{
	char	*var;
	int		i;
	int		len;

	i = 0;
	var = malloc(sizeof(char));
	if (!var)
		handle_error(ERR_MALLOC, MALLOC_FAILED);
	var[0] = '\0';
	len = ft_strlen(var_name);
	while (g_msh.env[i] && g_msh.env[i] != NULL)
	{
		if (ft_strncmp(var_name, g_msh.env[i], len) == 0)
		{
			if (g_msh.env[i][len] && g_msh.env[i][len] == '=')
			{
				free(var);
				var = ft_strdup(g_msh.env[i] + len + 1);
				break ;
			}
		}
		i++;
	}
	set_space(var);
	return (var);
}

/*
 ** Insert the environment variable value inside the command
 */

char	*rebuild_cmd(char *full_cmd, int pos_i, char *var, int len_var_name)
{
	char	*new_cmd;
	int		i;
	int		j;

	new_cmd = ft_calloc(ft_strlen(var) - len_var_name
			 + ft_strlen(full_cmd) + 2, sizeof(char));
	i = -1;
	while (i++ < pos_i - 1)
		new_cmd[i] = full_cmd[i];
	while (var && *var)
	{
		new_cmd[i++] = *var;
		var++;
	}
	j = 0;
	while (full_cmd[pos_i + len_var_name + j])
	{
		new_cmd[i++] = full_cmd[pos_i + len_var_name + j++];
	}
	new_cmd[i] = '\0';
	free(full_cmd);
	return (new_cmd);
}

char	*insert_msh_status(int pos_i, char *full_cmd)
{
	char	*new_cmd;
	char	*status;

	status = ft_itoa(g_msh.status);
	if (!status)
		handle_error(ERR_MALLOC, MALLOC_FAILED);
	new_cmd = rebuild_cmd(full_cmd, pos_i, status, 2);
	free(status);
	return (new_cmd);
}

/*
 ** The purpose of this function is to substitute $VAR with the corresponding
 ** environment var if it exist and rebuild the command by inserting the right
 ** value inside
 */

char	*set_env_var(char *full_cmd, int *i)
{
	int		len_var;
	int		pos_i;
	char	*var_name;
	char	*var;

	pos_i = *i;
	len_var = 1;
	*i = *i + 1;
	if (full_cmd[pos_i + 1] && full_cmd[pos_i + 1] == '?')
		full_cmd = insert_msh_status(pos_i, full_cmd);
	else
	{
		while (ft_isalnum_underscore(full_cmd[(*i)++]))
			len_var++;
		var_name = malloc(sizeof(char) * (len_var));
		ft_strlcpy(var_name, full_cmd + pos_i + 1, len_var);
		var = find_var(var_name);
		free(var_name);
		full_cmd = rebuild_cmd(full_cmd, pos_i, var, len_var);
		*i = pos_i + (int)ft_strlen(var) - 1;
		free(var);
	}
	return (full_cmd);
}
