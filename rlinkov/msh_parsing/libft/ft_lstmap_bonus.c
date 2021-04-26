/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 11:39:39 by chrisduvivi       #+#    #+#             */
/*   Updated: 2021/04/02 20:00:18 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**  Iterates the list lst and applies the function f
**	to the content of each element. Creates a new list
**	resulting of the successive applications of the
**	function f.
**
**	Itère sur la liste lst et applique la fonction f au
**	contenu de chaque élément. Crée une nouvelle liste
**	résultant des applications successives de f. la
**	fonction del est la pour detruire le contenu d un
**	element si necessaire
*/

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head_lst;
	t_list	*new;

	if (!lst || !f)
		return (NULL);
	head_lst = NULL;
	while (lst)
	{
		new = ft_lstnew((*f)(lst->content));
		if (!new)
		{
			ft_lstclear(&head_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&head_lst, new);
		lst = lst->next;
	}
	return (head_lst);
}
