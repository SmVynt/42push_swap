/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_commands_rr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 18:59:06 by psmolin           #+#    #+#             */
/*   Updated: 2025/06/06 12:04:53 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_rra(t_stack **a)
{
	if (!*a || !(*a)->prev)
		return (1);
	ft_roll_down(a);
	ft_print("rra\n");
	return (0);
}

int	ft_rrb(t_stack **b)
{
	if (!*b || !(*b)->prev)
		return (1);
	ft_roll_down(b);
	ft_print("rrb\n");
	return (0);
}

int	ft_rrr(t_stack **a, t_stack **b)
{
	int	done;

	done = 0;
	if ((*a) && (*a)->prev)
	{
		ft_roll_down(a);
		done = 1;
	}
	if ((*b) && (*b)->prev)
	{
		ft_roll_down(b);
		done = 1;
	}
	if (done == 0)
		return (1);
	ft_print("rrr\n");
	return (0);
}

// sa: swap a - swap the first 2 elements at the top of stack a. Do nothing if there is only one or no elements.
// sb: swap b - swap the first 2 elements at the top of stack b. Do nothing if there is only one or no elements.
// ss: sa and sb at the same time.
// pa: push a - take the first element at the top of b and put it at the top of a. Do nothing if b is empty.
// pb: push b - take the first element at the top of a and put it at the top of b. Do nothing if a is empty.
// ra: rotate a - shift up all elements of stack a by 1. The first element becomes the last one.
// rb: rotate b - shift up all elements of stack b by 1. The first element becomes the last one.
// rr: ra and rb at the same time.
// rra: reverse rotate a - shift down all elements of stack a by 1. The last element becomes the first one.
// rrb: reverse rotate b - shift down all elements of stack b by 1. The last element becomes the first one.
// rrr: rra and rrb at the same time.
