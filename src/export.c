/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlinkov <rlinkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 14:36:16 by rlinkov           #+#    #+#             */
/*   Updated: 2021/06/09 15:13:58 by rlinkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_msh	g_msh;

/*
 ** This function free the array of string ENV
 */

void	free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		free(env[i]);
		i++;
	}
	free(env);
}

/*
 ** This function create a new key with is associated value
 ** Then return it
 */

char	*create_new_env_var(char *key, char *value)
{
	int		i;
	int		size_key;
	int		size_value;
	char	*str;

	i = 0;
	size_key = (int)ft_strlen(key);
	size_value = (int)ft_strlen(value);
	str = malloc(size_key + size_value + 2);
	if (!str)
		handle_error(ERR_MALLOC);
	while (i < size_key)
		str[i++] = *(key++);
	str[i] = '=';
	i++;
	while (i < size_value + size_key + 1)
	{
		str[i] = *value;
		i++;
		value++;
	}
	str[i] = '\0';
	return (str);
}

/*
 ** This function update the value of a key
 ** It create a new entry in env if the key doesn't already exist
 */

void	add_var_to_env(char *key, char *value)
{
	int		env_size;
	char	**new_env;

	if (is_key_existing(key))
		set_env_value(key, value);
	else
	{
		env_size = 0;
		while (g_msh.env[env_size++] != NULL)
			env_size++;
		new_env = malloc(sizeof(char *) * (env_size + 2));
		env_size = 0;
		while (g_msh.env[env_size] != NULL)
		{
			new_env[env_size] = ft_strdup(g_msh.env[env_size]);
			env_size++;
		}
		new_env[env_size] = create_new_env_var(key, value);
		new_env[env_size + 1] = NULL;
		free_env(g_msh.env);
		g_msh.env = new_env;
	}
}

/*
 ** Append a value to the value of an existing environment var
 **/

void	append_var_to_env(char *key, char *value)
{
	char	*n_key;
	char	*n_value;
	char	*temp;
	int		i;

	n_key = malloc(ft_strlen(key) - 1);
	if (!n_key)
		handle_error(ERR_MALLOC);
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
		if (temp[i] == SPACE)
			temp[i] = ' ';
		i++;
	}
	n_value = malloc(sizeof(char) * (ft_strlen(temp) + ft_strlen(value) + 1));
	if (!n_value)
	{
		free(n_key);
		handle_error(ERR_MALLOC);
	}
	ft_strlcpy(n_value, temp, ft_strlen(temp) + 1);
	ft_strlcat(n_value, value, ft_strlen(temp) + ft_strlen(value) + 1);
	set_env_value(n_key, n_value);
	free(n_key);
	free(n_value);
	free(temp);
}

/*
 ** This function allow us to create new environment 
 ** variable or update existing one
 ** If the key exist, is value must be replaced by the new one
 ** If the key doesn't exist, it must be created 
 ** and associated with the new value
 ** The key can only start with alpha char
 ** The key can only contain alphanumeric char
 ** If the key ends with a "+" the new value must be 
 ** concatenate with the pre-existing value
 */

void	msh_bi_export(t_cmd_table t_cmd)
{
	char	*key;
	char	*value;
	int		i;
	int		pos_equal;

	i = 0;
	while (i < (int)ft_strlen(t_cmd.argv[1]) && t_cmd.argv[1][i] != '=')
		i++;
	if (i == 0 || t_cmd.argv[1][0] == '$' || !is_key_valid(t_cmd.argv[1], i))
	{
		printf("msh: export: `%s': not a valid identifier\n", t_cmd.argv[1]);
		return ;
	}
	if (t_cmd.argv[1][i] != '=')
		return ;
	key = malloc(sizeof(char) * i);
	if (!key)
		handle_error(ERR_MALLOC);
	ft_strlcpy(key, t_cmd.argv[1], i + 1);
	pos_equal = i;
	i = 0;
	while (i + pos_equal < (int)ft_strlen(t_cmd.argv[1]))
		i++;
	value = malloc(sizeof(char) * i);
	if (!value)
	{
		free(key);
		handle_error(ERR_MALLOC);
	}
	ft_strlcpy(value, t_cmd.argv[1] + pos_equal + 1, i);
	if (is_key_valid(key, (int)ft_strlen(key)) == 2)
		append_var_to_env(key, value);
	else
		add_var_to_env(key, value);
	free(key);
	free(value);
}
