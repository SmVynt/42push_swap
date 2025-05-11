/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:34:48 by psmolin           #+#    #+#             */
/*   Updated: 2025/05/11 23:02:19 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int arc, char **argv)
{
	t_stack	*A;
	t_stack	*B;

	if (arc < 2)
		return (0);
	A = NULL;
	B = NULL;
	ft_read_args(arc, argv, &A);
	ft_print_stack(&A);
	printf("---switch---\n");
	ft_switch(&A);
	ft_print_stack(&A);
	ft_print_stack(&B);
	printf("---A->B-----\n");
	ft_move(&A, &B);
	ft_print_stack(&A);
	ft_print_stack(&B);
	printf("---A->B-----\n");
	ft_move(&A, &B);
	ft_print_stack(&A);
	ft_print_stack(&B);
	printf("---A->B-----\n");
	ft_move(&A, &B);
	ft_print_stack(&A);
	ft_print_stack(&B);
	printf("---B->A-----\n");
	ft_move(&B, &A);
	ft_print_stack(&A);
	ft_print_stack(&B);
	printf("---roll A---\n");
	ft_roll_down(&A);
	ft_print_stack(&A);
	ft_print_stack(&B);
	printf("---A->B-----\n");
	ft_move(&A, &B);
	ft_print_stack(&A);
	ft_print_stack(&B);
	printf("---A <-> B--\n");
	ft_swap(&A, &B);
	ft_print_stack(&A);
	ft_print_stack(&B);
	ft_free(&A);
	ft_free(&B);
	printf("------------\n");
	ft_print_stack(&A);
	ft_print_stack(&B);
	(void)B;
	return (0);
}
