/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 11:52:06 by cduvivie          #+#    #+#             */
/*   Updated: 2021/04/02 20:29:49 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** initialize a stuck
*/

t_stack	*ft_stack_init(void)
{
	t_stack	*stack;

	stack = malloc(sizeof(t_stack));
	if (!stack)
		return (NULL);
	stack->head = NULL;
	stack->tail = NULL;
	stack->size = 0;
	return (stack);
}

/*
** push to stack: append to the top (to head)
*/

void	ft_stack_push(t_stack *stack, t_list *node)
{
	t_list	*tmp;

	tmp = NULL;
	if (stack->size != 0 && stack->head != NULL)
		tmp = stack->head;
	stack->head = node;
	node->next = tmp;
	if (stack->size == 0)
		stack->tail = node;
	stack->size++;
}

/*
** pop from stack: retrive element from top of stack (from head)
*/

t_list	*ft_stack_pop(t_stack *stack)
{
	t_list	*res;

	if (stack->size == 0 || stack->head == NULL)
		return (NULL);
	res = stack->head;
	stack->head = stack->head->next;
	if (stack->head == NULL)
		stack->tail = NULL;
	stack->size--;
	return (res);
}
