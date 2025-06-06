/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lists2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:35:02 by psmolin           #+#    #+#             */
/*   Updated: 2025/06/06 11:00:56 by psmolin          ###   ########.fr       */
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

int	ft_solve(t_stack **a, t_stack **b)
{
	(void)a;
	(void)b;
	printf("sorted\n");
	return (0);
}
