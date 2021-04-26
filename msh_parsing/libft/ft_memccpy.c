/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 14:18:59 by cduvivie          #+#    #+#             */
/*   Updated: 2021/04/02 20:10:00 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	- Description
**	Copy no more than N bytes of SRC to DST, stopping when C is found.
**	Return the position in DST one byte past where C was copied, or
**	NULL if C was not found in the first N bytes of SRC.
*/

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	if (s == d)
		return ((void *)d);
	while (n--)
	{
		*d++ = *s++;
		if (*d == (unsigned char)c)
			return ((void *)d);
	}
	return (NULL);
}
