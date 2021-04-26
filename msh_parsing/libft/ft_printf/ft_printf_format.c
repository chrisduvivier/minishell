/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_format.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 15:09:01 by cduvivie          #+#    #+#             */
/*   Updated: 2021/04/07 23:53:46 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	- Description:
**	handle the flags of ft_printf
**		• [-] left justify.
**		• [0] leading zero fill.
**		• [.] precision : minimum number of digits to be written.
**		• [*] The width is not specified in the format string, but as an
**			additional integer value argument preceding the argument
**			that has to be formatted.
**		• [+] Append sign (+ or -) to decimal conversion.
**		• [ ] Append space ` ` for positive, and `-` to negative number.
**		• [#] Append hex format to string for %x and %X.
**		• ['] Add thousand seperator for decimal conversion.
**	- Return Value:
**		The converted input as a string.
**		NULL is returned if error happens.
*/

static t_printf_lst	*read_flags(const char **format, t_printf_lst *node,
								va_list *valist)
{
	while (**format)
	{
		if (**format == '-' && (*format)++)
			node->flags.left = 1;
		else if (**format == '0' && (*format)++)
			node->flags.zeropad = 1;
		else if (**format == ' ' && (*format)++)
			node->flags.space = 1;
		else if (**format == '+' && (*format)++)
			node->flags.plus = 1;
		else if (**format == '#' && (*format)++)
			node->flags.sharp = 1;
		else if (**format == '\'' && (*format)++)
			node->flags.apostrophe = 1;
		else if (ft_isdigit(**format))
			node->flags.min_w = ft_pf_atoi(format);
		else if (**format == '*' && (*format)++)
			node->flags.min_w = va_arg(*valist, int);
		else if (**format == '.' && (*format)++ && ++(node->flags.precision))
			read_flags_helper(format, node, valist);
		else
			break ;
	}
	return (node);
}

static t_printf_lst	*read_len_modifier(const char **format, t_printf_lst *node)
{
	while (**format)
	{
		if (**format == 'l' && (*format)++)
			node->flags.l++;
		else if (**format == 'h' && (*format)++)
			node->flags.h++;
		else
			break ;
	}
	return (node);
}

/*
**	- Description:
**	handle the basic '%' argument type converion of ft_printf:
**		• %c print a single character
**		• %s print a string of characters
**		• %p prints the pointer.
**		• %d print a decimal (base 10) number
**		• %i print an integer in base 10
**		• %u print an unsigned decimal (base 10) number
**		• %x print a number in hexidecimal with lowercase abc... (base 16)
**		• %X print a number in hexidecimal with uppercase ABC... (base 16)
**		• %% print a percent sign (\% also works)
*/

t_printf_lst	*ft_pf_read_argument(const char **format, va_list *valist,
					t_printf_lst *node)
{
	free(node->str);
	node->str = NULL;
	if (**format == 'c')
		node = ft_pf_convert_c(node, va_arg(*valist, int));
	else if (**format == 's')
		node = ft_pf_convert_s(node, va_arg(*valist, char *));
	else if (**format == 'p')
		node = ft_pf_convert_p(node, va_arg(*valist, uintmax_t));
	else if (**format == 'd' || **format == 'i')
		node = ft_pf_convert_d(node, va_arg(*valist, int));
	else if (**format == 'u')
		node = ft_pf_convert_u(node, va_arg(*valist, unsigned int));
	else if (**format == 'x')
		node = ft_pf_convert_x(node, va_arg(*valist, unsigned int), 'x');
	else if (**format == 'X')
		node = ft_pf_convert_x(node, va_arg(*valist, unsigned int), 'X');
	else if (**format == '%')
		node = ft_pf_convert_pc(node, '%');
	node->percent = **format;
	(*format)++;
	return (node);
}

/*
**	Clean function that manages the flags to avoid conflicting conversion.
**	It also handle weird case (negative min_w given as parameter `*`) adds
**	a left align flag to the format (`-`).
*/

static t_printf_lst	*clean_flags(t_printf_lst *n)
{
	if (n->flags.min_w < 0)
		n->flags.left = 1;
	n->flags.min_w = ft_abs(n->flags.min_w);
	if (n->flags.max_w < 0)
	{
		n->flags.precision = 0;
		n->flags.max_w = 0;
	}
	if (n->flags.zeropad && n->flags.left)
		n->flags.zeropad = 0;
	if (n->percent == 'u')
	{
		n->flags.plus = 0;
		n->flags.space = 0;
	}
	if (n->percent == '%')
	{
		n->flags.precision = 0;
		n->flags.max_w = 0;
	}
	return (n);
}

/*
**	Handles the format of the string.
*/

t_printf_lst	*ft_pf_format_handler(const char **format, va_list *valist,
					t_printf_lst *node)
{
	node = read_flags(format, node, valist);
	node = read_len_modifier(format, node);
	if (node->flags.h || node->flags.l)
		node = ft_pf_read_argument_bonus(format, valist, node);
	else
		node = ft_pf_read_argument(format, valist, node);
	node = clean_flags(node);
	if (!node->error && node->percent)
		node = ft_pf_apply_flags(valist, node);
	return (node);
}
