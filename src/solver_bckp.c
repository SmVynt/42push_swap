/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver_bckp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 20:16:32 by psmolin           #+#    #+#             */
/*   Updated: 2025/06/09 00:00:10 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ft_calccomplexity(t_stacks *stacks)
{
	int	i;
	int	size;

	i = 0;
	size = stacks->size_a;
	while (size >= 3)
	{
		size = size / 3;
		i++;
	}
	stacks->complexity = i;
}

static void ft_swap_butterfly(t_stacks *stacks, int comp)
{
	int i;
	int size;
	int val;

	i = 0;
	size = stacks->size_a;
	while (i++ < size)
	{
		val = ft_num3n((*(stacks->a))->value, comp);
		if (val == 2)
			ft_ra(stacks);
		if (val == 1)
			ft_pb(stacks);
		if (val == 0)
		{
			ft_pb(stacks);
			ft_rb(stacks);
		}
	}
	size = stacks->size_b;
	i = 0;
	while (i++ < size)
	{
		val = ft_num3n((*(stacks->b))->value, comp);
		if (val == 1)
			ft_pa(stacks);
		if (val == 0)
		{
			ft_rrb(stacks);
			ft_pa(stacks);
		}
	}
}

int	ft_solve_bckp(t_stacks *stacks)
{
	int	i;

	i = 0;
	ft_calccomplexity(stacks);
	i = 0;
	while (i <= stacks->complexity)
	{
		ft_swap_butterfly(stacks, i);
		i++;
	}
	return (0);
}
