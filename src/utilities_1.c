/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlinkov <rlinkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 11:13:31 by cduvivie          #+#    #+#             */
/*   Updated: 2021/06/09 16:39:22 by rlinkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_msh g_msh;

/*
**  clean up t_cmd->argv and argc by removing empty argument.
**  @params:
**      *t_cmd: ptr to the command table
*/

void	clean_empty_arg(t_cmd_table *t_cmd)
{
	char	**new_argv;
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (i < t_cmd->argc)
	{
		if (t_cmd->argv[i][0] != '\0')
			count++;
		i++;
	}
	new_argv = (char **)ft_calloc(count + 1, sizeof(char *));
	if (!new_argv)
		exit(1);    //TODO
	i = 0;
	count = 0;
	while (i < t_cmd->argc)
	{
		if (t_cmd->argv[i] != NULL && t_cmd->argv[i][0] != '\0')
			new_argv[count++] = ft_strdup(t_cmd->argv[i]);
		free(t_cmd->argv[i++]);
	}
	new_argv[count] = NULL;
	t_cmd->argv = new_argv;
	t_cmd->argc = count;
}

/*
 ** As the key of the environment variable can contain "_"
 ** ft_isalpha is not sufficient to check if the key is correct
 */

int	ft_isalpha_underscore(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_');
}

/*
 ** As the key of the environment variable can contain "_"
 ** ft_isalnum is not sufficient to check if the key is correct
 */

int	ft_isalnum_underscore(int c)
{
	return (ft_isdigit(c) || ft_isalpha_underscore(c));
}

/*
 ** Check if the key is valid
 ** It must contain only alphanum char
 ** It must begin with only alpha char
 ** If the key end with a '+' the value must be append to te pre-existing one
 */

int	is_key_valid(char *key, int size)
{
	int	i;

	if (size != 0)
	{
		if (!ft_isalpha_underscore(key[0]))
			return (0);
		if (key[size - 1] == '+')
			return (2);
		i = 1;
		while (i < size)
		{
			if (!ft_isalnum_underscore(key[i]))
				return (0);
			i++;
		}
	}
	return (1);
}

/*
 ** This function check if the key already exist
 ** Return 1 if it exist
 ** Return 0 if it doesn't exist
 */

int	is_key_existing(char *key)
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
				return (1);
		}
		i++;
	}
	return (0);
}

/*
** FREE an array of string terminated by a NULL
*/

void	free_split(char **strs)
{
	int	i;

	i = 0;
	while (strs[i] != 0)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}