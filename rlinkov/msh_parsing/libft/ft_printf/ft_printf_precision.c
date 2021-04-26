/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_precision.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 14:38:00 by cduvivie          #+#    #+#             */
/*   Updated: 2021/04/07 20:07:07 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_printf_lst	*num_conv_precision(t_printf_lst *node)
{
	int	pad_len;
	int	num_sep;

	pad_len = node->flags.max_w - count_digit(node->str);
	if (node->flags.apostrophe)
	{
		if (node->str[0] == '+' || node->str[0] == '-')
			num_sep = ((node->str_len - 1) / 3) - 1;
		else
			num_sep = (node->str_len / 3) - 1;
		pad_len = pad_len - num_sep;
	}
	if (node->flags.max_w == 0 && node->zero)
	{
		if (node->str_len > 1)
			node->str[1] = '\0';
		else
			node->str[0] = '\0';
		node->str_len = ft_strlen(node->str);
	}
	else if (pad_len > 0)
		node = ft_pf_apply_zero_pad(node, pad_len, ft_pf_check_sign(node));
	node->flags.zeropad = 0;
	return (node);
}

static t_printf_lst	*hex_precision(t_printf_lst *node)
{
	int	pad_len;

	pad_len = node->flags.max_w - node->str_len;
	if (node->flags.max_w == 0 && node->zero)
	{
		if (node->str_len > 1)
			node->str[1] = '\0';
		else
			node->str[0] = '\0';
		node->str_len = ft_strlen(node->str);
	}
	else if (pad_len > 0)
	{
		node = ft_pf_apply_zero_pad(node, pad_len, 0);
	}
	node->flags.zeropad = 0;
	return (node);
}

static t_printf_lst	*p_precision(t_printf_lst *node)
{
	if (node->flags.max_w == 0 && node->zero)
	{
		node->str = ft_substr_clean(node->str, 0, 2);
		node->str_len = ft_strlen(node->str);
	}
	else if (node->flags.max_w > node->str_len)
	{
		if (node->zero)
			node = ft_pf_apply_zero_pad(node, node->flags.max_w - 1, 0);
		else
			node = ft_pf_apply_zero_pad(node,
					node->flags.max_w - node->str_len + 2, 0);
	}
	return (node);
}

static t_printf_lst	*s_precision(t_printf_lst *node)
{
	node->str = ft_substr_clean(node->str, 0, node->flags.max_w);
	if (!node->str)
	{
		node->error = 1;
		return (node);
	}
	node->str_len = ft_strlen(node->str);
	return (node);
}

/*
**	Handle precision to the formatted string.
**	if HEX CONVERSION:
**		- pad `0`.
**	else if NUMBER CONVERSION (except for HEX)
**		- case for str = '0'
**		- if max_field_width > str_len, we can only add 0 padding.
**		  Because precision refers to the min num of DIGITS for NUM_CONVERSION.
**	else if POINTER CONVERSION:
**		- case for str = '0'.
**		- otherwise, pad `0`.
**	else if STRING CONVERSION:
**		- if max field width (max_w) < str_len, we need to cut the string.
*/

t_printf_lst	*ft_pf_apply_precision(t_printf_lst *node)
{
	if (ft_strchr("xX", node->percent))
		node = hex_precision(node);
	else if (node->num_conv)
		node = num_conv_precision(node);
	else if (node->percent == 'p')
		node = p_precision(node);
	else if (node->flags.max_w < node->str_len)
		node = s_precision(node);
	return (node);
}
