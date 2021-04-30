/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 16:04:46 by cduvivie          #+#    #+#             */
/*   Updated: 2021/04/07 23:53:57 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	The atoi() function converts the initial portion of the string pointed
**	to by str to int representation.
**	Return 0 by default
*/

int	ft_pf_atoi(const char **format)
{
	unsigned long long	result;

	result = 0;
	while (**format >= '0' && **format <= '9')
	{
		result = result * 10 + (**format - '0');
		(*format)++;
	}
	return ((int)(result));
}

int	append_zero_helper(t_printf_lst *node, char	**ptr, size_t i)
{
	*(*ptr)++ = node->str[i];
	i++;
	*(*ptr)++ = node->str[i];
	i++;
	return (i);
}

void	read_flags_helper(const char **format, t_printf_lst *node,
								va_list *valist)
{
	if (**format == '*' && (*format)++)
	{
		node->flags.max_w = va_arg(*valist, int);
	}
	else
		node->flags.max_w = ft_pf_atoi(format);
}
