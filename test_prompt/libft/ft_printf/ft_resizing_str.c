/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_resizing_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:41:15 by cduvivie          #+#    #+#             */
/*   Updated: 2021/04/04 14:38:01 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	ft_pf_push(): append char and double size of array s[] when array is full.
**	pop(): remove char and halve size of array s[] when array is 1/4 full.
**	ft_pf_resize(): resize array and copy its content.
*/

t_printf_lst	*ft_pf_resize(t_printf_lst *lst, size_t len)
{
	char	*copy;
	size_t	i;

	copy = ft_calloc(len + 1, sizeof(char));
	if (!copy)
	{
		lst->error = 1;
		if (lst && lst->str)
			free(lst->str);
		return (lst);
	}
	i = 0;
	if (lst->str)
	{
		while (lst->str[i])
		{
			copy[i] = lst->str[i];
			i++;
		}
		free(lst->str);
	}
	lst->str = copy;
	lst->str_len = len;
	lst->i = i;
	return (lst);
}

/*
**	Append char to the string and resize if necessary.
**	Resize occurs when the index reached the length of the string s_len.
**	item: char to append to the string
*/

t_printf_lst	*ft_pf_push(t_printf_lst *lst, char item)
{
	if (lst->i == lst->str_len)
	{
		lst = ft_pf_resize(lst, 2 * lst->str_len);
		if (lst->error)
			return (lst);
	}
	lst->str[lst->i] = item;
	lst->i = lst->i + 1;
	return (lst);
}

/*
**	Remove the last char in the string and resize if necessary.
*/

t_printf_lst	*ft_pf_pop(t_printf_lst *lst)
{
	lst->str[lst->i] = '\0';
	lst->i = lst->i - 1;
	if (lst->i > 0 && lst->i == (lst->str_len / 4))
	{
		lst = ft_pf_resize(lst, lst->str_len / 2);
		if (lst->error)
			return (lst);
	}
	return (lst);
}
