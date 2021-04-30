/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 13:34:13 by cduvivie          #+#    #+#             */
/*   Updated: 2021/04/02 19:59:16 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
**	The strdup() function allocates sufficient memory for a copy of the
**	string s1, does the copy, and returns a pointer to it.
*/

char	*gnl_ft_strdup(const char *s1)
{
	char	*str;
	char	*p;

	if (!s1)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!str)
		return (NULL);
	p = str;
	while (*s1)
		*p++ = *s1++;
	*p = '\0';
	return (str);
}

/*
**	- Description
**	locates the FIRST occurrence of c (converted to a char)
**	in the string pointed to by s.  The terminating null character
**	is considered to be part of the string; therefore if c is `\0', the
**	functions locate the terminating `\0'.
**
**	- Return Values
**	return a pointer to the located
**	character, or NULL if the character does not appear in the string.
*/

char	*gnl_ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)(s));
		s++;
	}
	if (*s == (char)c)
		return ((char *)(s));
	return (NULL);
}

/*
**	- Description:
**	Allocates (with malloc(3)) and returns a substring
**	from the string given in argument.
**	The substring begins at index ’start’ and is of maximum size ’len’.
**	- Return value:
**	The substring. NULL if the allocation fails.
*/

char	*gnl_ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	substr = malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	i = 0;
	if (s && start < (unsigned int)ft_strlen(s))
	{
		while (s[start + i] && i < len)
		{
			substr[i] = s[start + i];
			i++;
		}
	}
	substr[i] = '\0';
	return (substr);
}
