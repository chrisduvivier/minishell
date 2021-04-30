/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 13:51:17 by cduvivie          #+#    #+#             */
/*   Updated: 2021/04/02 20:22:09 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	- Description:
**  Allocates (with malloc(3)) and returns a copy of the string
**	given as argument without the characters specified in the set argument
**	at the beginning and the end of the string.
**	- Return value:
**	The trimmed string. NULL if the allocation fails.
**
** ft_strtrim("11202:Chris:0105", "1234567890:" -> "Chris")
** ft_strtrim("112Chris1996January05", "1234567890:" -> "Chris1996January")
*/

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	if (!s1 || !set)
		return ((char *)s1);
	start = 0;
	while (s1[start])
	{
		if (ft_strchr(set, s1[start]) == NULL)
			break ;
		start++;
	}
	end = ft_strlen(s1) - 1;
	while (end > 0)
	{
		if (ft_strchr(set, s1[end]) == NULL)
			break ;
		end--;
	}
	if (start > end || ft_strlen(s1) == 0)
		return (ft_substr(s1, 0, 0));
	return (ft_substr(s1, start, (end - start + 1)));
}
