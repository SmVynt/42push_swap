/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:34:48 by psmolin           #+#    #+#             */
/*   Updated: 2025/06/09 23:44:50 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int arc, char **argv)
{
	t_stack		*a;
	t_stack		*b;
	t_stacks	stacks;

	if (arc < 2)
		return (0);
	a = NULL;
	b = NULL;
	stacks.a = &a;
	stacks.b = &b;
	stacks.size_a = 0;
	stacks.size_b = 0;
	ft_read_args(arc, argv, &stacks);
	if (*error_status() != 0)
		ft_exit_error("Invalid input", &stacks);
	if (ft_check_input(stacks.a) == -1)
		ft_exit_error("Duplicate values found", &stacks);
	stacks.max_value = stacks.size_a - 1;
	ft_solve(&stacks);
	ft_free(stacks.a);
	ft_free(stacks.b);
	return (0);
}
