/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 12:19:48 by chrisduvivi       #+#    #+#             */
/*   Updated: 2021/04/02 20:06:44 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Deletes and frees the given element and every
**	successor of that element, using the function del and free(3)
**	Finally, the pointer to the list must be set to NULL
*/

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*next;
	t_list	*current;

	if (lst && del)
	{
		current = *lst;
		while (current)
		{
			if (current->content)
				(*del)(current->content);
			next = current->next;
			free(current);
			current = next;
		}
		*lst = NULL;
	}
}
