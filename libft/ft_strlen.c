/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 10:46:21 by cduvivie          #+#    #+#             */
/*   Updated: 2021/06/24 21:24:10 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/*
**	Assumes that the array of string is fill with non NULL str
**	except teh last element.
*/

size_t	ft_str_array_len(const char **s)
{
	size_t	i;

	i = 0;
	if (s)
	{
		while (s[i] != NULL)
		{
			i++;
		}
	}
	return (i);
}