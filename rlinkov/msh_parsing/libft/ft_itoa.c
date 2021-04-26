/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 18:08:11 by cduvivie          #+#    #+#             */
/*   Updated: 2021/04/06 18:49:39 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_itoa_helper(char **str, int i, int n, long *nbr)
{
	char	*ptr;

	ptr = *str;
	if (n < 0)
		i = i + 1;
	ptr[i--] = '\0';
	if (n < 0)
		ptr[0] = '-';
	else
		ptr[0] = '\0';
	if (n < 0)
		*nbr = -(long)n;
	else
		*nbr = (long)n;
	if (n == 0)
		ptr[i] = '0';
	else
		ptr[i] = '\0';
	return (i);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*str;
	long	nbr;

	nbr = (long)n;
	i = 1;
	nbr = nbr / 10;
	while (nbr)
	{
		nbr = nbr / 10;
		i++;
	}
	if (n == 0)
		str = (char *)malloc(i + 1);
	else
		str = (char *)malloc(i + 2);
	if (!str)
		return (NULL);
	i = ft_itoa_helper(&str, i, n, &nbr);
	while (nbr)
	{
		str[i--] = (char)((nbr % 10) + '0');
		nbr /= 10;
	}
	return (str);
}

int	ft_uitoa_helper(char **str, int i, unsigned int n, unsigned long *nbr)
{
	char	*ptr;

	ptr = *str;
	ptr[i--] = '\0';
	ptr[0] = '\0';
	*nbr = (unsigned long)n;
	ptr[i] = '0';
	if (n != 0)
		ptr[i] = '\0';
	return (i);
}

/*
**	itoa that gets unsigned integer as input.
*/

char	*ft_uitoa(unsigned int n)
{
	int				i;
	char			*str;
	unsigned long	nbr;

	nbr = (unsigned long)n;
	i = 1;
	nbr = nbr / 10;
	while (nbr)
	{
		nbr = nbr / 10;
		i++;
	}
	if (n == 0)
		str = (char *)malloc(i + 1);
	else
		str = (char *)malloc(i + 2);
	if (!str)
		return (NULL);
	i = ft_uitoa_helper(&str, i, n, &nbr);
	while (nbr)
	{
		str[i--] = (char)((nbr % 10) + '0');
		nbr /= 10;
	}
	return (str);
}
