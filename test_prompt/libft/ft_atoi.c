/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:53:01 by cduvivie          #+#    #+#             */
/*   Updated: 2021/04/04 14:19:08 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	The atoi() function converts the initial portion of the string pointed
**	to by str to int representation.
*/

int	ft_atoi(const char *str)
{
	unsigned long long	result;
	int					sign;

	result = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		sign = 1;
		if (*str++ == '-')
			sign = -1;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		if (result > LONG_MAX)
		{
			if (sign == -1)
				return (0);
			return (-1);
		}
		str++;
	}
	return ((int)(sign * result));
}

/*
**	The atoi() function converts the initial portion of the string pointed
**	to by str to int representation. pointer to str moves as the atoi reads.
**	It therefore finishes where the string of number finishes
*/

int	ft_atoi_w_p(const char **str)
{
	unsigned long long	result;
	int					sign;

	result = 0;
	sign = 1;
	while (ft_isspace(**str))
		(*str)++;
	if (**str == '-' || **str == '+')
	{
		sign = 1;
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	while (**str >= '0' && **str <= '9')
	{
		result = result * 10 + (**str - '0');
		if (result > LONG_MAX && sign == -1)
			return (0);
		else if (result > LONG_MAX)
			return (-1);
		(*str)++;
	}
	return ((int)(sign * result));
}
