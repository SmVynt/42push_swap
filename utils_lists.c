/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lists.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:35:02 by psmolin           #+#    #+#             */
/*   Updated: 2025/05/06 12:24:22 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*ft_add_new(int value_init, char parent)
{
	t_stack *new;

	new = (t_stack *)malloc(sizeof(t_stack));
	if (!new)
		return (NULL);
	new->value_init = value_init;
	new->parent = parent;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_stack	*ft_add_back(t_stack **stack, t_stack *new)
{
	t_stack *last;

	if (!new)
		return (NULL);
	if (!*stack)
	{
		*stack = new;
		new->next = new;
		new->prev = new;
		return (new);
	}
	last = (*stack)->prev;
	last->next = new;
	new->prev = last;
	new->next = *stack;
	(*stack)->prev = new;
	return (new);
}

t_stack	*ft_add_front(t_stack **stack, t_stack *new)
{
	t_stack *last;

	if (!stack || !new)
		return (NULL);
	if (!*stack)
	{
		*stack = new;
		new->next = new;
		new->prev = new;
		return (new);
	}
	last = (*stack)->prev;
	new->next = *stack;
	new->prev = last;
	last->next = new;
	(*stack)->prev = new;
	*stack = new;
	return (new);
}

void	ft_free(t_stack **stack)
{
	t_stack *tmp;
	t_stack *cur;

	if (!stack || !*stack)
		return;
	cur = *stack;
	(*stack)->prev->next = NULL;
	while (cur)
	{
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	*stack = NULL;
}
