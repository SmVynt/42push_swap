/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 20:16:32 by psmolin           #+#    #+#             */
/*   Updated: 2025/06/09 23:36:08 by psmolin          ###   ########.fr       */
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
	int		i;
	int		size;
	float	k;
	int		val_min;

	i = 0;
	k = 0.783f;
	size = stacks->size_a;
	while (stacks->size_a > 3 && i < 10000)
	{
		i++;
		val_min = size - (int)((float)(stacks->size_a) * k);
		if (val_min > size - 3)
			val_min = size - 3;
		if ((*(stacks->a))->value < val_min)
			ft_pb(stacks);
		else
			ft_ra(stacks);
	}
	ft_swap3(stacks);
}

static int	ft_calculate_left_price(t_stacks *stacks, int value)
{
	int		i;
	t_stack	*cur;

	i = 0;
	cur = *stacks->a;
	while (i < stacks->size_a)
	{
		if (value > cur->prev->value && value < cur->value)
			break;
		if (cur->prev->value == stacks->max_value && value < cur->value)
		 	break;
		i++;
		cur = cur->next;
	}
	if (i > (stacks->size_a / 2))
		i = i - stacks->size_a;
	//printf ("%d\n", i);
	return (i);
}

static int	ft_worst_price(int a, int b)
{
	if (a == 0 || b == 0)
	{
		if (a < 0)
			return (-a);
		else if (a > 0)
			return (a);
		else if (b < 0)
			return (-b);
		return (b);
	}
	if (a > 0 && b > 0)
	{
		if (a > b)
			return (a);
		return (b);
	}
	if (a < 0 && b < 0)
	{
		if (a < b)
			return ( -a);
		return (-b);
	}
	if (a - b < 0)
		return (b - a);
	return (a - b);
}

static t_prices	ft_calculate_prices(t_stacks *stacks)
{
	int			i;
	int			best_total;
	t_prices	best_prices;
	t_stack		*cur;

	i = -1;
	cur = *stacks->b;
	best_total = stacks->max_value;
	while (++i < stacks->size_b)
	{
		cur->price = i;
		if (i > stacks->size_b / 2)
			cur->price = i - stacks->size_b;
		// cur->price *= -1;
		cur->price_left = ft_calculate_left_price(stacks, cur->value);
		cur->price_total = ft_worst_price(cur->price, cur->price_left);
		//printf("_%d = %d %d\n",cur->price_total, cur->price_left, cur->price);
		if (best_total > cur->price_total)
		{
			best_total = cur->price_total;
			best_prices.price_a = cur->price_left;
			best_prices.price_b = cur->price;
		}
		cur = cur->next;
	}
		//printf(" %d = %d %d\n",best_total, best_prices.price_a, best_prices.price_b);
	return(best_prices);
}

static int	ft_dec(int a)
{
	if (a < 0)
		return (1);
	if (a > 0)
		return (-1);
	return (0);
}

static void	ft_move_cheapest(t_stacks *stacks, t_prices prices)
{
	while (prices.price_a != 0 || prices.price_b !=0)
	{
		if (prices.price_a > 0 && prices.price_b > 0)
			ft_rr(stacks);
		else if (prices.price_a < 0 && prices.price_b < 0)
			ft_rrr(stacks);
		else
		{
			if (prices.price_a > 0)
				ft_ra(stacks);
			if (prices.price_a < 0)
				ft_rra(stacks);
			if (prices.price_b > 0)
				ft_rb(stacks);
			if (prices.price_b < 0)
				ft_rrb(stacks);
		}
		prices.price_a += ft_dec(prices.price_a);
		prices.price_b += ft_dec(prices.price_b);
	}
	ft_pa(stacks);
}

static void ft_swap_back(t_stacks *stacks)
{
	t_prices	prices;
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
	int	i;

	i = 0;
	(void)i;
	if (stacks->size_a <=3)
		return(ft_swap3(stacks), 0);
	ft_swap_dirty(stacks);
	ft_swap_back(stacks);
	ft_fix(stacks);
	return (0);
}
