/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 20:16:32 by psmolin           #+#    #+#             */
/*   Updated: 2025/06/11 15:24:18 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ft_swap3(t_stacks *stacks)
{
	int	v0;
	int	v1;
	int	v2;

	v0 = (*(stacks->a))->value;
	v1 = (*(stacks->a))->next->value;
	v2 = (*(stacks->a))->prev->value;
	if (v2 > v0 && v2 > v1)
	{
		if (v1 < v0)
			ft_sa(stacks);
	}
	if (v0 > v1 && v0 > v2)
	{
		ft_ra(stacks);
		if (v1 > v2)
			ft_sa(stacks);
	}
	if (v1 > v0 && v1 > v2)
	{
		ft_rra(stacks);
		if (v2 > v0)
			ft_sa(stacks);
	}
}

static void	ft_swap_dirty(t_stacks *stacks)
{
	int		size;
	float	k;
	int		val_min;

	k = 0.8f;
	size = stacks->size_a;
	while (stacks->size_a > 3)
	{
		val_min = size - (int)((float)(stacks->size_a) * k);
		if (val_min > size - 3)
			val_min = size - 3;
		if ((*(stacks->a))->value < val_min)
			ft_pb(stacks);
		else
		{
			if (ft_nearest_small(stacks, val_min) < 0)
				ft_rra(stacks);
			else
				ft_ra(stacks);
		}
	}
	ft_swap3(stacks);
}

static void	ft_swap_back(t_stacks *stacks)
{
	t_prcs	prices;

	while (stacks->size_b > 0)
	{
		prices = ft_calculate_prices(stacks);
		ft_move_cheapest(stacks, prices);
	}
}

static void	ft_fix(t_stacks *stacks)
{
	while ((*stacks->a)->value != 0)
	{
		if ((*stacks->a)->value > stacks->max_value / 2)
			ft_ra(stacks);
		else
			ft_rra(stacks);
	}
}

int	ft_solve(t_stacks *stacks)
{
	if (stacks->size_a <= 3)
	{
		ft_swap3(stacks);
		return (0);
	}
	ft_swap_dirty(stacks);
	ft_swap_back(stacks);
	ft_fix(stacks);
	return (0);
}
