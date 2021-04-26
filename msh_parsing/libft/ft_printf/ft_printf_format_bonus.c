/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_format_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 14:47:42 by cduvivie          #+#    #+#             */
/*   Updated: 2021/04/07 20:07:17 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	- Description:
**	handler the '%' argument type converion of ft_printf
**	• h: A following integer conversion corresponds to a short int or
**		unsigned short int argument, or a following n conversion corresponds to
**		a pointer to a short int argument.
**	• hh: A following integer conversion corresponds to a signed char or
**		unsigned char argument, or a following n conversion corresponds to
**		a pointer to a signed char argument.
**	• ll: A following integer conversion corresponds to a long long int or
**		unsigned long long int argument, or a following n conversion
**		corresponds to a pointer to a long long int argument.
*/

static t_printf_lst	*read_argument_h(const char **format, va_list *valist,
									t_printf_lst *n)
{
	free(n->str);
	n->str = NULL;
	if (**format == 'd' || **format == 'i')
		n = ft_pf_convert_d(n, (short)va_arg(*valist, int));
	else if (**format == 'u')
		n = ft_pf_convert_u(n, (unsigned short)va_arg(*valist, int));
	else if (**format == 'x')
		n = ft_pf_convert_x(n, (unsigned short)va_arg(*valist, int), 'x');
	else if (**format == 'X')
		n = ft_pf_convert_x(n, (unsigned short)va_arg(*valist, int), 'X');
	else
		return (n = ft_pf_read_argument(format, valist, n));
	n->percent = **format;
	(*format)++;
	return (n);
}

static t_printf_lst	*read_argument_hh(const char **format, va_list *valist,
									t_printf_lst *n)
{
	free(n->str);
	n->str = NULL;
	if (**format == 'd' || **format == 'i')
		n = ft_pf_convert_d(n, (signed char)va_arg(*valist, int));
	else if (**format == 'u')
		n = ft_pf_convert_u(n, (unsigned char)va_arg(*valist, int));
	else if (**format == 'x')
		n = ft_pf_convert_x(n, (unsigned char)va_arg(*valist, int), 'x');
	else if (**format == 'X')
		n = ft_pf_convert_x(n, (unsigned char)va_arg(*valist, int), 'X');
	else
		return (n = ft_pf_read_argument(format, valist, n));
	n->percent = **format;
	(*format)++;
	return (n);
}

static t_printf_lst	*read_argument_l(const char **format, va_list *valist,
									t_printf_lst *n)
{
	free(n->str);
	n->str = NULL;
	if (**format == 'd' || **format == 'i')
		n = ft_pf_convert_d(n, va_arg(*valist, long int));
	else if (**format == 'u')
		n = ft_pf_convert_u(n, va_arg(*valist, unsigned long int));
	else if (**format == 'x')
		n = ft_pf_convert_x(n, va_arg(*valist, unsigned long int), 'x');
	else if (**format == 'X')
		n = ft_pf_convert_x(n, va_arg(*valist, unsigned long int), 'X');
	else
		return (n = ft_pf_read_argument(format, valist, n));
	n->percent = **format;
	(*format)++;
	return (n);
}

static t_printf_lst	*read_argument_ll(const char **format, va_list *valist,
									t_printf_lst *n)
{
	free(n->str);
	n->str = NULL;
	if (**format == 'd' || **format == 'i')
		n = ft_pf_convert_d(n, va_arg(*valist, long long int));
	else if (**format == 'u')
		n = ft_pf_convert_u(n, va_arg(*valist, unsigned long long int));
	else if (**format == 'x')
		n = ft_pf_convert_x(n, va_arg(*valist, unsigned long long int), 'x');
	else if (**format == 'X')
		n = ft_pf_convert_x(n, va_arg(*valist, unsigned long long int), 'X');
	else
		return (n = ft_pf_read_argument(format, valist, n));
	n->percent = **format;
	(*format)++;
	return (n);
}

t_printf_lst	*ft_pf_read_argument_bonus(const char **format,
							va_list *valist, t_printf_lst *node)
{
	if (node->flags.h == 1 && !(node->flags.l))
		node = read_argument_h(format, valist, node);
	else if (node->flags.h == 2 && !(node->flags.l))
		node = read_argument_hh(format, valist, node);
	else if (node->flags.l == 1 && !(node->flags.h))
		node = read_argument_l(format, valist, node);
	else if (node->flags.l == 2 && !(node->flags.h))
		node = read_argument_ll(format, valist, node);
	return (node);
}
