/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_msh.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlinkov <rlinkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 17:20:57 by rlinkov           #+#    #+#             */
/*   Updated: 2021/04/26 17:49:04 by rlinkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

static int	count_size_tab(char *str, char c)
{
	int		i;
	int		nb_word;

	i = 0;
	nb_word = 0;
	if (!str || str[0] == '\0')
		return (0);
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		nb_word++;
		while (str[i] != c && str[i])
			i++;
	}
	if (str[i - 1] == c)
		nb_word--;
	return (nb_word);
}

static int	size_elem(char *str, char c)
{
	int		i;

	i = 0;
	while (str[i] != c && str[i])
		i++;
	return (i);
}

static char	**free_tab(char **tab, int index)
{
	int	i;

	i = 0;
	while (i < index - 1)
		free(tab[i++]);
	free(tab);
	return (NULL);
}

char	**ft_split_msh(char const *s, char c)
{
	char	**tab;
	int		size_tab;
	int		size_to_copy;
	int		start;
	int		i;

	i = 0;
	start = 0;
	size_tab = count_size_tab((char *)s, c);
	tab = (char **)malloc(sizeof(char *) * (size_tab + 1));
	if (!s || !tab)
		return ((char **) NULL);
	while (i < size_tab && s[start] != '\0')
	{
		while (s[start] == c && s[start] != '\0')
			start++;
		size_to_copy = size_elem((char *)s + start, c);
		tab[i++] = ft_substr(s, start, size_to_copy);
		if (!(tab[i - 1]))
			return (free_tab(tab, i));
		start += size_to_copy;
	}
	tab[size_tab] = 0;
	return (tab);
}