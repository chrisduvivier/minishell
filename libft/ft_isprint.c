/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 11:54:07 by cduvivie          #+#    #+#             */
/*   Updated: 2021/04/02 20:10:25 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	tests for any printing character, including space (` ').
**	The value of the argument must be representable as an
**	unsigned char or the value of EOF.
*/

int	ft_isprint(int c)
{
	return (c >= ' ' && c <= '~');
}
