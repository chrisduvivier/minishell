/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 18:08:11 by cduvivie          #+#    #+#             */
/*   Updated: 2021/04/06 18:50:02 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_llitoa_helper(char **str, int i, long long int n,
	long long int *nbr)
{
	char	*ptr;

	ptr = *str;
	if (n < 0)
		i++;
	ptr[i--] = '\0';
	if (n < 0)
		ptr[0] = '-';
	else
		ptr[0] = '\0';
	if (n < 0)
		*nbr = -(long long int)n;
	else
		*nbr = (long long int)n;
	if (n == 0)
		ptr[i] = '0';
	else
		ptr[i] = '\0';
	return (i);
}

char	*ft_llitoa(long long int n)
{
	int				i;
	char			*str;
	long long int	nbr;

	nbr = n;
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
	i = ft_llitoa_helper(&str, i, n, &nbr);
	while (nbr)
	{
		str[i--] = (char)((nbr % 10) + '0');
		nbr /= 10;
	}
	return (str);
}

int	ft_ullitoa_helper(char **str, int i, unsigned long long int n,
	unsigned long long int *nbr)
{
	char	*ptr;

	ptr = *str;
	ptr[i--] = '\0';
	ptr[0] = '\0';
	*nbr = n;
	if (n == 0)
		ptr[i] = '0';
	else
		ptr[i] = '\0';
	return (i);
}

char	*ft_ullitoa(unsigned long long int n)
{
	int						i;
	char					*str;
	unsigned long long int	nbr;

	nbr = n;
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
	i = ft_ullitoa_helper(&str, i, n, &nbr);
	while (nbr)
	{
		str[i--] = (char)((nbr % 10) + '0');
		nbr /= 10;
	}
	return (str);
}
