/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 15:27:35 by rlinkov           #+#    #+#             */
/*   Updated: 2021/06/21 21:38:11 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_msh	g_msh;

void	append_var_to_env_2(char *temp, char *n_key, char *value)
{
	char	*n_value;

	n_value = malloc(sizeof(char) * (ft_strlen(temp) + ft_strlen(value) + 1));
	if (!n_value)
	{
		free(n_key);
		handle_error(ERR_MALLOC, MALLOC_FAILED);
	}
	ft_strlcpy(n_value, temp, ft_strlen(temp) + 1);
	ft_strlcat(n_value, value, ft_strlen(temp) + ft_strlen(value) + 1);
	set_env_value(n_key, n_value);
	free(n_key);
	free(n_value);
	free(temp);
}

/*
 ** Append a value to the value of an existing environment var
 **/

void	append_var_to_env(char *key, char *value)
{
	char	*n_key;
	char	*temp;
	int		i;

	n_key = malloc(ft_strlen(key) - 1);
	if (!n_key)
		handle_error(ERR_MALLOC, MALLOC_FAILED);
	ft_strlcpy(n_key, key, ft_strlen(key));
	if (!is_key_existing(n_key))
	{
		free(n_key);
		return (add_var_to_env(key, value));
	}
	temp = find_var(n_key);
	i = 0;
	while (i < (int)ft_strlen(temp))
	{
		if (temp[i] == SPACE_TOK)
			temp[i] = ' ';
		i++;
	}
	append_var_to_env_2(temp, n_key, value);
}
