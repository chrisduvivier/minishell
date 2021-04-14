/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 17:30:26 by cduvivie          #+#    #+#             */
/*   Updated: 2021/04/04 13:49:13 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	n_words(char const *str, char sep)
{
	int	count;

	count = 0;
	while (*str)
	{
		while (*str && *str == sep)
			str++;
		if (*str && *str != sep)
		{
			count++;
			while (*str && *str != sep)
				str++;
		}
	}
	return (count);
}

static char	*malloc_word(char const *str, char sep)
{
	int		i;
	char	*word;

	i = 0;
	while (str[i] && str[i] != sep)
		i++;
	word = ft_substr(str, 0, i);
	if (!word)
		return (NULL);
	return (word);
}

static void	free_array(char **array, int i)
{
	if (array)
	{
		while (i >= 0)
		{
			if (array[i])
				free(array[i--]);
		}
		free(array);
	}
}

char	**ft_split_init_helper(char const *s, char c)
{
	if (!s)
		return (NULL);
	return ((char **)malloc(sizeof(char *) * (n_words(s, c) + 1)));
}

/*
**	- Description:
**  Allocates (with malloc(3)) and returns an array of strings
**  obtained by splitting `s` using the character `c` as a delimiter.
**  The array must be ended by a NULL pointer.
**	- Return value:
**	The array of new strings result of the split.
**  NULL if the allocation fails.
*/

char	**ft_split(char const *s, char c)
{
	char	**split_tab;
	int		i;

	split_tab = ft_split_init_helper(s, c);
	if (!split_tab)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			split_tab[i++] = malloc_word(s, c);
			if (!split_tab[i++])
			{
				free_array(split_tab, i - 1);
				return (NULL);
			}
			while (*s && *s != c)
				s++;
		}
	}
	split_tab[i] = NULL;
	return (split_tab);
}
