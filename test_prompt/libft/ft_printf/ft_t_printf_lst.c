/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_t_printf_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 15:41:52 by cduvivie          #+#    #+#             */
/*   Updated: 2021/04/07 20:10:43 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	Allocates memory and returns a new element.
**	The variable next is initialized to NULL.
*/

t_printf_lst	*ft_pf_t_lstnew(void)
{
	t_printf_lst	*lst;

	lst = (t_printf_lst *)ft_calloc(1, sizeof(t_printf_lst));
	if (!lst)
		return (NULL);
	lst->str = (char *)ft_calloc(BUFF_SIZE + 1, sizeof(char));
	if (!lst->str)
		return (NULL);
	lst->percent = '\0';
	lst->i = 0;
	lst->str_len = BUFF_SIZE;
	lst->next = NULL;
	return (lst);
}

/*
**	Takes as a parameter an element and frees the
**	memory of the string if it exists.
*/

void	ft_pf_t_lstdelone(t_printf_lst *lst)
{
	if (lst)
	{
		if (lst->str)
		{
			free(lst->str);
			lst->str = NULL;
		}
		free(lst);
		lst = NULL;
	}
}

/*
**	Returns the last element of the list.
*/

t_printf_lst	*ft_pf_t_lstlast(t_printf_lst *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

/*
**	Adds the element new at the end of the list.
*/

void	ft_pf_t_lstadd_back(t_printf_lst **head, t_printf_lst *new)
{
	t_printf_lst	*last;

	if (head && new)
	{
		if (!(*head))
			*head = new;
		else
		{
			last = ft_pf_t_lstlast(*head);
			last->next = new;
		}
	}
}

/*
**	Deletes and frees the given element and every
**	successor of that element.
**	Finally, the pointer to the list must be set to NULL
*/

void	ft_pf_t_lstclear(t_printf_lst **head)
{
	t_printf_lst	*next;
	t_printf_lst	*current;

	if (head)
	{
		current = *head;
		while (current)
		{
			next = current->next;
			ft_pf_t_lstdelone(current);
			current = next;
		}
		*head = NULL;
	}
}
