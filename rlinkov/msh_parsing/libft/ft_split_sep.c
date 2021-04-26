/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_sep.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 16:03:58 by cduvivie          #+#    #+#             */
/*   Updated: 2021/04/02 20:29:06 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	n_words(char const *str, const char *sep)
{
	int	count;

	count = 0;
	while (*str)
	{
		while (*str && ft_strchr(sep, *str))
			str++;
		if (*str && !(ft_strchr(sep, *str)))
		{
			count++;
			while (*str && !(ft_strchr(sep, *str)))
				str++;
		}
	}
	return (count);
}

static char	*malloc_word(char const *str, const char *sep)
{
	int		i;
	char	*word;

	i = 0;
	while (str[i] && !(ft_strchr(sep, str[i])))
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

void	ft_split_free(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
}

/*
**	- Description:
**  Allocates (with malloc(3)) and returns an array of strings
**  obtained by splitting `s` using the characters in `sep` as a delimiter.
**  The array must be ended by a NULL pointer.
**	- Return value:
**	The array of new strings result of the split.
**  NULL if the allocation fails.
**
**	With norm update, deleted first protection. Just check s exists before call
**
*/

char	**ft_split_sep(char const *s, const char *sep)
{
	char	**split_tab;
	int		i;

	split_tab = (char **)malloc(sizeof(char *) * (n_words(s, sep) + 1));
	if (!split_tab)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && ft_strchr(sep, *s))
			s++;
		if (*s && !(ft_strchr(sep, *s)))
		{
			split_tab[i++] = malloc_word(s, sep);
			if (!split_tab[i++])
			{
				free_array(split_tab, i - 1);
				return (NULL);
			}
			while (*s && !(ft_strchr(sep, *s)))
				s++;
		}
	}
	split_tab[i] = NULL;
	return (split_tab);
}
