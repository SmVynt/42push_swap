/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_solver.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 20:16:32 by psmolin           #+#    #+#             */
/*   Updated: 2025/06/10 01:02:17 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	ft_calculate_left_price(t_stacks *stacks, int value)
{
	int		i;
	t_stack	*cur;

	i = 0;
	cur = *stacks->a;
	while (i < stacks->size_a)
	{
		if (value > cur->prev->value && value < cur->value)
			break ;
		if (cur->prev->value == stacks->max_value && value < cur->value)
			break ;
		i++;
		cur = cur->next;
	}
	if (i > (stacks->size_a / 2))
		i = i - stacks->size_a;
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
			return (-a);
		return (-b);
	}
	if (a - b < 0)
		return (b - a);
	return (a - b);
}

t_prcs	ft_calculate_prices(t_stacks *stacks)
{
	int			i;
	int			best_total;
	t_prcs		best_prcs;
	t_stack		*cur;

	i = -1;
	cur = *stacks->b;
	best_total = stacks->max_value;
	while (++i < stacks->size_b)
	{
		cur->price = i;
		if (i > stacks->size_b / 2)
			cur->price = i - stacks->size_b;
		cur->price_left = ft_calculate_left_price(stacks, cur->value);
		cur->price_total = ft_worst_price(cur->price, cur->price_left);
		if (best_total > cur->price_total)
		{
			best_total = cur->price_total;
			best_prcs.price_a = cur->price_left;
			best_prcs.price_b = cur->price;
		}
		cur = cur->next;
	}
	return (best_prcs);
}

static int	ft_dec(int a)
{
	if (a < 0)
		return (1);
	if (a > 0)
		return (-1);
	return (0);
}

void	ft_move_cheapest(t_stacks *stacks, t_prcs prices)
{
	while (prices.price_a != 0 || prices.price_b != 0)
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
