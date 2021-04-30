/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conversion_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 15:04:42 by cduvivie          #+#    #+#             */
/*   Updated: 2021/04/07 19:17:21 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_chartostr(int i)
{
	char	*str;

	str = ft_calloc(2, sizeof(char));
	if (!str)
		return (NULL);
	str[0] = (char)i;
	str[1] = '\0';
	return (str);
}

/*
**	handling of `%c` format.
*/

t_printf_lst	*ft_pf_convert_c(t_printf_lst *node, uintmax_t c)
{
	node->str = ft_chartostr(c);
	if (!node->str)
	{
		node->error = 1;
		return (node);
	}
	node->str_len = 1;
	return (node);
}

/*
**	Print "%". Does not get affected by any flags.
*/

t_printf_lst	*ft_pf_convert_pc(t_printf_lst *node, int c)
{
	node->str = ft_chartostr('%');
	if (!node->str)
	{
		node->error = 1;
		return (node);
	}
	node->str_len = 1;
	return (node);
}

/*
**	handling of `%s` format. returns `(null)` when the given
**	string src is NULL. strdup otherwise.
*/

t_printf_lst	*ft_pf_convert_s(t_printf_lst *node, const char *src)
{
	if (!src)
		node->str = ft_strdup("(null)");
	else
		node->str = ft_strdup(src);
	if (!node->str)
	{
		node->error = 1;
		return (node);
	}
	node->str_len = ft_strlen(node->str);
	return (node);
}
