/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itohex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:04:11 by cduvivie          #+#    #+#             */
/*   Updated: 2021/04/07 19:44:09 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	ft_decimal_to_base: gets the character's corresponding
**	decimal number (ASCII table), and calculates the value in the given base.
*/

static int	ft_decimal_to_hex(uintmax_t nbr, const char *base, char **str,
							int i)
{
	uintmax_t	quotient;
	uintmax_t	remainder;
	char		*hex;

	quotient = nbr / 16;
	remainder = nbr % 16;
	hex = *str;
	if (nbr >= 16)
	{
		i = ft_decimal_to_hex(quotient, base, str, i);
		hex[i] = base[remainder];
		return (i + 1);
	}
	else
	{
		hex[i] = base[remainder];
		return (i + 1);
	}
}

/*
**	Returns the number of digits after conversion to hexadecimal.
*/

static size_t	len_in_hex(uintmax_t nbr)
{
	size_t	count;

	count = 1;
	while (nbr >= 16)
	{
		nbr = nbr / 16;
		count++;
	}
	return (count);
}

/*
**	Appends "0x" or "0X" format depending on the given flag
**	(passed as char format).
*/

char	*ft_pf_append_hex_format(char *hex, char format)
{
	char	*res;

	if (!hex)
		return (NULL);
	if (format && format == 'X')
		res = ft_strjoin("0X", hex);
	else
		res = ft_strjoin("0x", hex);
	free(hex);
	return (res);
}

/*
**	Number to hexadecimal convertion. char format defines the format
**	of the conversion (uppercase or lowercase).
*/

char	*ft_itohex(uintmax_t nbr, char format)
{
	char		*str;
	const char	*base;
	size_t		len;

	if (format && format == 'X')
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	len = len_in_hex(nbr);
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	str[len] = '\0';
	ft_decimal_to_hex(nbr, base, &str, 0);
	return (str);
}
