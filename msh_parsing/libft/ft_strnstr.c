/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:11:58 by cduvivie          #+#    #+#             */
/*   Updated: 2021/04/02 19:53:09 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	- Description
**	function locates the first occurrence of `the null-terminated` string find
**	in the string str, where not more than len characters are searched.
**
**	- Return Values
**	If find is an empty string, str is returned; if find occurs
**	nowhere in str, NULL is returned; otherwise a pointer to the
**	first character of the first occurrence of find is returned.
*/

char	*ft_strnstr(const char *str, const char *find, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*find == '\0')
		return ((char *)(str));
	while (str[i] && i < len)
	{
		j = 0;
		while (str[i + j] == find[j] && i + j < len)
		{
			if (find[j + 1] == '\0')
				return ((char *)(&str[i]));
			j++;
		}
		i++;
	}
	return (NULL);
}
