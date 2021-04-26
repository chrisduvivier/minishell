/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 17:44:15 by cduvivie          #+#    #+#             */
/*   Updated: 2021/04/04 14:40:13 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	Exit function called upon error. Deletes the linked list.
*/

static int	free_and_exit(t_printf_lst **head_lst)
{
	ft_pf_t_lstclear(head_lst);
	return (-1);
}

/*
**	Takes a node of the list and print the stored sting.
*/

static int	ft_printf_putstr(t_printf_lst *node)
{
	int	len;

	if (node->percent)
		len = node->str_len;
	else
		len = node->i;
	write(1, node->str, len);
	return (len);
}

/*
**	Iterate through the linked list and print the stored sting.
**	Returns the total number of char printed.
*/

static int	t_printf_lstprint(t_printf_lst **head_lst)
{
	size_t			res;
	t_printf_lst	*current;

	res = 0;
	current = *head_lst;
	while (current)
	{
		res += ft_printf_putstr(current);
		current = current->next;
	}
	return (res);
}

/*
**	- Description:
**		gets a new node, read the input (normal or with flag) and add to list.
**		return -1 upon error. 0 on success.
*/

static int	read_to_lst(const char *format, t_printf_lst **head_lst,
						va_list *valist)
{
	t_printf_lst	*node;

	while (*format)
	{
		node = ft_pf_t_lstnew();
		if (!node)
			return (-1);
		ft_pf_t_lstadd_back(head_lst, node);
		if (*format == '%' && format++ && *format)
		{
			node = ft_pf_format_handler(&format, valist, node);
			if (node->error)
				return (-1);
		}
		else
		{
			while (*format && *format != '%')
			{
				node = ft_pf_push(node, *format++);
				if (node->error)
					return (-1);
			}
		}
	}
	return (0);
}

/*
**	- Description
**	• It will manage the following conversions: c s p d i u x X %
**	• It will manage any combination of the following flags: ’-0.*’ and
**	  minimum field witdh
**
**	- Order
**	• % | Flags | Min field width | Period | Precision | Argument type
**
**	- Return Value
**		Return the number of bytes transmitted,
**		not including the null character [\0].
**		If an error was encountered, a negative value is output.
*/

int	ft_printf(const char *format, ...)
{
	int				result;
	va_list			valist;
	t_printf_lst	*head_lst;

	va_start(valist, format);
	head_lst = NULL;
	if (read_to_lst(format, &head_lst, &valist) < 0)
	{
		va_end(valist);
		return (free_and_exit(&head_lst));
	}
	result = t_printf_lstprint(&head_lst);
	ft_pf_t_lstclear(&head_lst);
	va_end(valist);
	return (result);
}
