/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:19:28 by cduvivie          #+#    #+#             */
/*   Updated: 2021/04/02 20:19:01 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	- DESCRIPTION
**	The memchr() function locates the first occurrence of c (converted to
**	an unsigned char) in string s.
**	- RETURN VALUES
**	The memchr() function returns a pointer to the byte located, or NULL
**	if no such byte exists within n bytes.
*/

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*str;

	str = (const unsigned char *)s;
	while (n--)
	{
		if (*str == (unsigned char)c)
			return ((void *)(str));
		str++;
	}
	return (NULL);
}
