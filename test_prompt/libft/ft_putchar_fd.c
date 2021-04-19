/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 13:00:26 by cduvivie          #+#    #+#             */
/*   Updated: 2019/10/22 13:03:00 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Outputs the character c to given file descriptor.
**	'1' for stdout, '2'	for	stderr.
*/

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
