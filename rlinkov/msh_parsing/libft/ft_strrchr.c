/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:53:40 by cduvivie          #+#    #+#             */
/*   Updated: 2021/04/02 20:18:46 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	- Description
**	locates the LAST occurrence of c (converted to a char)
**	in the string pointed to by s.  The terminating null character
**	is considered to be part of the string; therefore if c is `\0', the
**	functions locate the terminating `\0'.
**
**	- Return Values
**	return a pointer to the located
**	character, or NULL if the character does not appear in the string.
*/

char	*ft_strrchr(const char *s, int c)
{
	const char	*ptr;
	const char	*found;

	if (c == '\0')
		return (ft_strchr(s, '\0'));
	found = NULL;
	ptr = ft_strchr(s, c);
	while (ptr != NULL)
	{
		found = ptr;
		s = ptr + 1;
	}
	return ((char *)(found));
}
