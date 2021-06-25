/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 17:16:31 by rlinkov           #+#    #+#             */
/*   Updated: 2021/06/25 19:08:27 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_msh	g_msh;

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
	while (strs[i] != NULL)
	{
		free(strs[i]);
		strs[i] = NULL;
		i++;
	}
	free(strs);
	strs = NULL;
}

/*
**	1 if string contains a non empty char
*/

int	is_empty_str(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]) == 0)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

/*
**	Helper function for exec_cmd to set the value of the process id
** 	and wait for the execution of child process before proceeding in
**	parent. At end of child process, the exit status gets updated. 
*/

void	exec_cmd_helper(int pid)
{
	int	status;

	g_msh.pid = pid;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_msh.status = WEXITSTATUS(status);
}
