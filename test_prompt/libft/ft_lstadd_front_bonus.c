/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 11:02:51 by chrisduvivi       #+#    #+#             */
/*   Updated: 2019/10/17 13:37:25 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Adds the element new at the beginning of the list
*/

void	ft_lstadd_front(t_list **alst, t_list *new)
{
	if (new && alst)
	{
		new->next = *alst;
		*alst = new;
	}
}
