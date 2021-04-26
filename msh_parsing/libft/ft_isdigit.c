/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 11:12:06 by cduvivie          #+#    #+#             */
/*   Updated: 2021/04/02 19:54:07 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isdigit_string(const char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (*str != '\0')
	{
		if (!(ft_isdigit(*str)))
			return (0);
		str++;
	}
	return (1);
}
