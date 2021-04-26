/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:53:40 by cduvivie          #+#    #+#             */
/*   Updated: 2021/04/02 20:01:04 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

char	*ft_strchr(const char *s, int c)
{
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
