/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:34:48 by psmolin           #+#    #+#             */
/*   Updated: 2025/05/06 12:26:03 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int arc, char **argv)
{
	t_stack	**A;
	t_stack	**B;

	if (arc < 2)
		return (0);
	ft_read_args(arc, argv, A);
	ft_print_stack(A);
	ft_free(A);
	return (0);
}
