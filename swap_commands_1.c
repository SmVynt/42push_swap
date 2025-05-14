/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_commands_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 18:59:06 by psmolin           #+#    #+#             */
/*   Updated: 2025/05/14 21:46:15 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_roll_up(t_stack **A)
{
	*A = (*A)->next;
}

void	ft_roll_down(t_stack **A)
{
	*A = (*A)->prev;
}

void	ft_swap(t_stack **A, t_stack **B)
{
	ft_move(A, B);
	ft_roll_up(B);
	ft_move(B, A);
	ft_roll_down(B);
}

void	ft_move(t_stack **SRC, t_stack **DST)
{
	t_stack	*tmp;

	if (!*SRC)
		return ;
	tmp = (*SRC);
	*SRC = (*SRC)->next;
	(*SRC)->prev = tmp->prev;
	(*SRC)->prev->next = *SRC;
	if (tmp->next == tmp)
		*SRC = NULL;
	ft_add_front(DST, tmp);
}

void	ft_switch(t_stack **S)
{
	t_stack	*n1;
	t_stack	*n2;

	n1 = (*S);
	n2 = (*S)->next;
	if (n1 == n2 || n1 == NULL || n2 == NULL)
		return ;
	n1->next = n2->next;
	n2->next->prev = n1;
	ft_add_front(S, n2);
}
