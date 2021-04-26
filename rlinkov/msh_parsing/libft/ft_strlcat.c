/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 12:55:30 by cduvivie          #+#    #+#             */
/*   Updated: 2019/11/18 11:22:55 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	- Description
**	The strlcat() function appends the NUL-terminated string src to
**	the end of dst (`dst[len_dst + i]`). It will append at most
**	`size - strlen(dst) - 1` bytes, NUL-terminating the result.
**	Note that a byte for the NUL should be included in size.
**	both src and dst must be NUL-terminated.
**
**	- Return Values
**	the total length of the string they tried to create.
**	if strlcat() traverses size characters without finding a NUL,
**	the length of the string is considered to be size and the destination string
**	will not be NUL-terminated (since there was no space for the NUL).ßß
*/

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (size && dst[i])
	{
		i++;
		size--;
	}
	if (size == 0)
		return (i + ft_strlen(src));
	while (size-- > 1 && src[j])
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	return (i + ft_strlen(src));
}
