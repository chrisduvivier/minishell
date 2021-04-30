/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_padding.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 13:09:21 by cduvivie          #+#    #+#             */
/*   Updated: 2021/04/06 23:49:02 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	Append space to the formatted string.
*/

static char	*append_space(t_printf_lst *node, size_t pad_len)
{
	size_t	i;
	char	*padding;
	char	*res;

	i = 0;
	padding = ft_calloc(node->str_len + pad_len + 1, sizeof(char));
	if (!padding)
		return (NULL);
	while (i < pad_len)
		padding[i++] = ' ';
	if (node->flags.left)
		res = ft_printf_strjoin(node->str, padding, node->str_len, pad_len);
	else
		res = ft_printf_strjoin(padding, node->str, pad_len, node->str_len);
	free(padding);
	return (res);
}

/*
**	Append zeros to the formatted string (only NUM_CONVERSION).
*/

static char	*append_zero(t_printf_lst *node, size_t pad_len, int sign,
						size_t i)
{
	char	*ptr;
	char	*res;

	i = 0;
	res = ft_calloc(node->str_len + pad_len + 1, sizeof(char));
	if (!res)
		return (NULL);
	ptr = res;
	if (sign && ++i)
		*ptr++ = sign;
	if (!(node->flags.precision) && node->flags.sharp
		&& ft_strchr("xX", node->percent) && !(ft_pf_is_zero(node->str)))
	{
		i = append_zero_helper(node, &ptr, i);
	}
	if (node->percent == 'p')
		i = append_zero_helper(node, &ptr, i);
	while (pad_len--)
		*ptr++ = '0';
	while (node->str[i])
		*ptr++ = node->str[i++];
	return (res);
}

t_printf_lst	*ft_pf_apply_zero_pad(t_printf_lst *node,
	size_t pad_len, int sign)
{
	char	*res;

	res = append_zero(node, pad_len, sign, 0);
	if (!res)
	{
		node->error = 1;
		return (node);
	}
	free(node->str);
	node->str = res;
	node->str_len = ft_strlen(node->str);
	return (node);
}

t_printf_lst	*ft_pf_apply_space_pad(t_printf_lst *node, size_t pad_len)
{
	char	*res;

	res = append_space(node, pad_len);
	if (!res)
	{
		node->error = 1;
		return (node);
	}
	free(node->str);
	node->str = res;
	node->str_len = pad_len + node->str_len;
	return (node);
}

/*
**	Handle minimum field width to the formatted string.
**	NUM_CONV and STR_CONV share the different treatment.
*/

t_printf_lst	*ft_pf_apply_min_w(t_printf_lst *node)
{
	int	pad_len;

	pad_len = node->flags.min_w - node->str_len;
	if (pad_len > 0)
	{
		if (node->num_conv)
		{
			if (node->flags.zeropad && !(node->flags.left))
				node = ft_pf_apply_zero_pad(node, pad_len,
						ft_pf_check_sign(node));
			else
				node = ft_pf_apply_space_pad(node, pad_len);
		}
		else
		{
			if (node->flags.zeropad && !(node->flags.left)
				&& node->flags.min_w > node->flags.max_w)
				node = ft_pf_apply_zero_pad(node, pad_len, 0);
			else
				node = ft_pf_apply_space_pad(node, pad_len);
		}
	}
	return (node);
}
