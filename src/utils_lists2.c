/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lists2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:35:02 by psmolin           #+#    #+#             */
/*   Updated: 2025/06/12 06:07:59 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_check_input(t_stack **stack)
{
	t_stack	*itmp;
	t_stack	*jtmp;
	int		checked;

	itmp = *stack;
	itmp->value = 0;
	checked = 0;
	while (checked == 0)
	{
		jtmp = itmp;
		itmp->value = 0;
		while (jtmp->next != itmp)
		{
			jtmp = jtmp->next;
			if (itmp->value_init > jtmp->value_init)
				itmp->value++;
			if (itmp->value_init == jtmp->value_init)
				return (-1);
		}
		itmp = itmp->next;
		if (itmp == *stack)
			checked = 1;
	}
	return (0);
}

int	ft_nearest_small(t_stacks *stacks, int val)
{
	int		i;
	t_stack	*back;
	t_stack	*front;

	i = 0;
	back = (*stacks->a)->prev;
	front = (*stacks->a)->next;
	while (i < stacks->max_value)
	{
		if (front->value < val)
			return (1);
		if (back->value < val)
			return (-1);
		i++;
		front = front->next;
		back = back->prev;
	}
	return (1);
}

int	ft_check_sort(t_stacks *stacks)
{
	int		i;
	t_stack	*cur;

	cur = *stacks->a;
	i = 0;
	if (*stacks->b)
		return (ft_print(COLOR_R"KO\n"COLOR_X), 1);
	while (cur->next != *stacks->a)
	{
		if (cur->next->value < cur->value)
			return (ft_print(COLOR_R"KO\n"COLOR_X), 1);
		cur = cur->next;
		i++;
	}
	return (ft_print(COLOR_G"OK\n"COLOR_X), 1);
}

int	is_sorted(t_stacks *stacks)
{
	int		i;
	t_stack	*cur;

	cur = *stacks->a;
	i = 0;
	if (*stacks->b)
		return (0);
	while (cur->next != *stacks->a)
	{
		if (cur->next->value < cur->value)
			return (0);
		cur = cur->next;
		i++;
	}
	return (1);
}
