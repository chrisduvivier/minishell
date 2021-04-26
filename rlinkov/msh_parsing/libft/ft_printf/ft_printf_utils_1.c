/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 16:04:46 by cduvivie          #+#    #+#             */
/*   Updated: 2021/04/07 19:58:02 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	Ensures to write '\0' char as part of the string when joininig strings.
*/

char	*ft_printf_strjoin(char const *s1, char const *s2,
							size_t len_s1, size_t len_s2)
{
	char	*res;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	res = ft_calloc(len_s1 + len_s2 + 1, sizeof(char));
	if (!res)
		return (NULL);
	while (j < len_s1)
		res[i++] = s1[j++];
	j = 0;
	while (j < len_s2)
		res[i++] = s2[j++];
	res[i] = '\0';
	return (res);
}

size_t	count_digit(char *str)
{
	size_t	i;

	i = 0;
	while (*str)
	{
		if (ft_isdigit(*str))
			i++;
		str++;
	}
	return (i);
}

/*
**	Negative numbers always print with a minus sign.
**		- append_zero must receive the '-' sign as its 1st char.
**	Positive numbers and zero print with a '+' sign only if [+] argument.
**	Positive numbers and zero print with a ' ' space if [ ] argument.
*/

char	ft_pf_check_sign(t_printf_lst *node)
{
	char	sign;

	sign = 0;
	if (node->str[0] == '-')
	{
		if (node->flags.precision || node->flags.zeropad)
			sign = '-';
	}
	else
	{
		if (node->flags.space)
			sign = ' ';
		if (node->flags.plus)
			sign = '+';
	}
	return (sign);
}

/*
**	check if:
**		- zero with + sign.
**		- all zeros.
*/

int	ft_pf_is_zero(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '+' && str[1] == '0' && str[2] == '\0')
		return (1);
	while (str[i])
	{
		if (str[i++] != '0')
			return (0);
	}
	return (1);
}

t_printf_lst	*ft_pf_append_sign(t_printf_lst *node)
{
	char	*tmp;
	char	*sign_str;

	if (node->str[0] != '-')
	{
		sign_str = ft_chartostr(ft_pf_check_sign(node));
		if (!sign_str)
		{
			node->error = 1;
			return (node);
		}
		tmp = ft_strjoin(sign_str, node->str);
		if (!tmp)
		{
			node->error = 1;
			free(sign_str);
			return (node);
		}
		free(node->str);
		free(sign_str);
		node->str = tmp;
		node->str_len = ft_strlen(node->str);
	}
	return (node);
}
