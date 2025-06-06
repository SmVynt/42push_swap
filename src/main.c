/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:34:48 by psmolin           #+#    #+#             */
/*   Updated: 2025/06/06 14:16:03 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// static void	print_a_b(t_stack *a, t_stack *b)
// {
// 	printf("A:");
// 	ft_print_stack(&a);
// 	printf("B:");
// 	ft_print_stack(&b);
// }

int	main(int arc, char **argv)
{
	t_stack	*a;
	t_stack	*b;

	if (arc < 2)
		return (0);
	a = NULL;
	b = NULL;
	ft_read_args(arc, argv, &a);
	if (*error_status() != 0)
		ft_exit_error("Invalid input", &a, &b);
	if (ft_check_input(&a) == -1)
		ft_exit_error("Duplicate values found", &a, &b);
	ft_print_stack(&a);
	ft_solve(&a, &b);
	ft_free(&a);
	ft_free(&b);
	printf("%d\n", ft_num2n(5, 0));
	printf("%d\n", ft_num2n(5, 1));
	printf("%d\n", ft_num2n(5, 2));
	printf("%d\n", ft_num2n(5, 3));
	printf("%d\n", ft_num2n(5, 4));
	printf("------------\n");
	printf("%d\n", ft_num3n(5, 0));
	printf("%d\n", ft_num3n(5, 1));
	printf("%d\n", ft_num3n(5, 2));
	printf("%d\n", ft_num3n(5, 3));
	printf("%d\n", ft_num3n(5, 4));
	return (0);
}

// int	main(int arc, char **argv)
// {
// 	t_stack	*a;
// 	t_stack	*b;
// 	if (arc < 2)
// 		return (0);
// 	a = NULL;
// 	b = NULL;
// 	ft_read_args(arc, argv, &a);
// 	ft_print_stack(&a);
// 	printf("---switch---\n");
// 	ft_switch(&a);
// 	print_a_b(a, b);
// 	printf("---A->B-----\n");
// 	ft_move(&a, &b);
// 	print_a_b(a, b);
// 	printf("---A->B-----\n");
// 	ft_move(&a, &b);
// 	print_a_b(a, b);
// 	printf("---A->B-----\n");
// 	ft_move(&a, &b);
// 	print_a_b(a, b);
// 	printf("---B->A-----\n");
// 	ft_move(&b, &a);
// 	print_a_b(a, b);
// 	printf("---roll A---\n");
// 	ft_roll_down(&a);
// 	print_a_b(a, b);
// 	printf("---A->B-----\n");
// 	ft_move(&a, &b);
// 	print_a_b(a, b);
// 	printf("---A <-> B--\n");
// 	ft_swap(&a, &b);
// 	print_a_b(a, b);
// 	ft_free(&a);
// 	ft_free(&b);
// 	printf("------------\n");
// 	print_a_b(a, b);
// 	return (0);
// }
