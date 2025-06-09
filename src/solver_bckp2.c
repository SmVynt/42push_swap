/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver_bckp2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 20:16:32 by psmolin           #+#    #+#             */
/*   Updated: 2025/06/09 00:21:35 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"


static void	ft_calccomplexity(t_stacks *stacks)
{
	int	i;
	int	size;

	i = 0;
	size = stacks->size_a;
	while (size >= 2)
	{
		size = size / 2;
		i++;
	}
	stacks->complexity = i;
}

// static void ft_sort(t_stacks *stacks, int comp)
// {
// 	int	i;
// 	int	val;
// 	int	size;

// 	i = 0;
// 	size = stacks->size_a;
// 	//printf(COLOR_R "%d\n" COLOR_X, comp);
// 	while (i < size)
// 	{
// 		val = ft_num3n((*(stacks->a))->value, comp);
// 		//printf(COLOR_G "val: %d -> %d\n"COLOR_X,(*(stacks->a))->value, val);
// 		if (val == 0)
// 		{
// 			ft_pb(stacks);
// 			ft_rb(stacks);
// 		}
// 		if (val == 1)
// 			ft_ra(stacks);
// 		else if (val == 2)
// 			ft_pb(stacks);
// 		i++;
// 	}
// }

// static void ft_swap_a(t_stacks *stacks, int comp, int curnum)
// {
// 	int	i;
// 	int	val;
// 	int	size;

// 	i = 0;
// 	size = stacks->size_a;
// 	while (i < size)
// 	{
// 		val = ft_num3n((*(stacks->a))->value, comp);
// 		//printf(COLOR_G "val: %d -> %d\n"COLOR_X,(*(stacks->a))->value, val);
// 		if (val == 0)
// 		{
// 			ft_pb(stacks);
// 			ft_rb(stacks);
// 		}
// 		if (val == 1)
// 			ft_ra(stacks);
// 		else if (val == 2)
// 			ft_pb(stacks);
// 		i++;
// 	}
// }

// static void ft_swap_a(t_stacks *stacks, int comp)
// {
// 	int	i;
// 	int	size;

// 	i = 0;
// 	size = stacks->size_a;
// 	while (i < size)
// 	{
// 		//printf("%d\n", ft_num2n((*(stacks->a))->value, comp));
// 		if (ft_num2n((*(stacks->a))->value, comp) == 1)
// 			ft_pb(stacks);
// 		else
// 		{
// 			ft_pb(stacks);
// 			ft_rb(stacks);
// 		}
// 		i++;
// 	}
// }

// static void ft_swap_b(t_stacks *stacks, int comp)
// {
// 	int	i;
// 	int	size;

// 	i = 0;
// 	size = stacks->size_b;
// 	while (i < size)
// 	{
// 		if (ft_num2n((*(stacks->b))->value, comp) == 1)
// 			ft_pa(stacks);
// 		else
// 		{
// 			ft_pa(stacks);
// 			ft_ra(stacks);
// 		}
// 		i++;
// 	}
// }

static void ft_swap_a(t_stacks *stacks, int comp)
{
	int	i;
	int	size;

	i = 0;
	(void)comp;
	size = stacks->size_a;
	while (i < size)
	{
		if (ft_num2n((*(stacks->a))->value, comp) == 0)
			ft_pb(stacks);
		else
			ft_ra(stacks);
		i++;
	}
	i = 0;
	size = stacks->size_a;
	while (i < size)
	{
		ft_pb(stacks);
		i++;
	}
}

static void ft_swap_b(t_stacks *stacks, int comp)
{
	int i;
	int size;

	i = 0;
	(void)comp;
	size = stacks->size_b;
	while (i < size)
	{
		if (ft_num2n((*(stacks->b))->value, comp) == 1)
			ft_pa(stacks);
		else
			ft_rb(stacks);
		i++;
	}
	i = 0;
	size = stacks->size_b;
	while (i < size)
	{
		ft_pa(stacks);
		i++;
	}
}

// static void ft_swap_0(t_stacks *stacks)
// {
// 	int i;
// 	int size;

// 	size = stacks->size_a;
// 	i = 0;
// 	while (i < size)
// 	{
// 		if (ft_num2n((*(stacks->a))->value, 0) == 1)
// 			ft_pb(stacks);
// 		else
// 			ft_ra(stacks);
// 		i++;
// 	}
// }

// static void ft_swap_fin(t_stacks *stacks, int comp)
// {
// 	int	size_a;
// 	int	size_b;
// 	int i;
// 	int v_a;
// 	int v_b;

// 	size_a = stacks->size_a;
// 	size_b = stacks->size_b;
// 	i = 0;
// 	while (i < size_a || i < size_b)
// 	{
// 		v_a = ft_num2n((*(stacks->a))->value, comp);
// 		v_b = ft_num2n((*(stacks->b))->value, comp);
// 		if (v_a == 0 && v_b == 0)
// 		{
// 			ft_ra(stacks);
// 			ft_pa(stacks);
// 			ft_ra(stacks);
// 		}
// 		if (v_a == 0 && v_b == 1)
// 			ft_rr(stacks);
// 		if (v_a == 1 && v_b == 0)
// 		{
// 			ft_pb(stacks);
// 			ft_rb(stacks);
// 			ft_pa(stacks);
// 			ft_ra(stacks);
// 		}
// 		if (v_a == 1 && v_b == 1)
// 		{
// 			ft_rb(stacks);
// 			ft_pb(stacks);
// 			ft_rb(stacks);
// 		}
// 		i++;
// 	}
// }

// static void ft_swap_comp(t_stacks *stacks, int comp)
// {
// 	int	size_a;
// 	int	size_b;
// 	int i;
// 	int v_a;
// 	int v_b;

// 	size_a = stacks->size_a;
// 	size_b = stacks->size_b;
// 	i = 0;
// 	while (i < size_a || i < size_b)
// 	{
// 		v_a = ft_num2n((*(stacks->a))->value, comp);
// 		v_b = ft_num2n((*(stacks->b))->value, comp);
// 		if (v_a == 0 && v_b == 0)
// 		{
// 			ft_ra(stacks);
// 			ft_pa(stacks);
// 			ft_ra(stacks);
// 		}
// 		if (v_a == 0 && v_b == 1)
// 			ft_rr(stacks);
// 		if (v_a == 1 && v_b == 0)
// 		{
// 			ft_pb(stacks);
// 			ft_rb(stacks);
// 			ft_pa(stacks);
// 			ft_ra(stacks);
// 		}
// 		if (v_a == 1 && v_b == 1)
// 		{
// 			ft_rb(stacks);
// 			ft_pb(stacks);
// 			ft_rb(stacks);
// 		}
// 		i++;
// 	}
// }

int	ft_solve_bckp2(t_stacks *stacks)
{
	int	i;

	ft_calccomplexity(stacks);
	i = 0;
(void)i;
	// printf("complexity: %d\n", stacks->complexity);
	// ft_swap_0(stacks);
	// ft_swap_comp(stacks, 1);
	while (i <= stacks->complexity)
	{
		ft_swap_a(stacks, i);
		i++;
		ft_swap_b(stacks, i);
		i++;
	}
	//ft_sort(stacks, stacks->complexity);
	//ft_sort(stacks, stacks->complexity - 1);
	// printf("sorted\n");
	return (0);
}
