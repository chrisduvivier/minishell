/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 13:04:28 by cduvivie          #+#    #+#             */
/*   Updated: 2019/11/22 11:11:55 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Outputs the string c to given file descriptor.
**	'1' for stdout, '2'	for	stderr.
*/

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}
