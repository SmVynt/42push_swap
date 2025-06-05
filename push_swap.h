/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 21:38:54 by psmolin           #+#    #+#             */
/*   Updated: 2025/06/05 10:07:57 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>

typedef struct s_stack	t_stack;

struct s_stack
{
	t_stack	**head;
	int		value_init;
	int		value;
	int		price;
	t_stack	*next;
	t_stack	*prev;
};

void	ft_read_args(int arc, char **argv, t_stack **A);
void	ft_print_stack(t_stack **stack);
t_stack	*ft_add_new(int value_init, t_stack **head);
t_stack	*ft_add_back(t_stack **stack, t_stack *new);
t_stack	*ft_add_front(t_stack **stack, t_stack *new);
void	ft_free(t_stack **stack);

void	ft_roll_up(t_stack **A);
void	ft_roll_down(t_stack **A);
void	ft_swap(t_stack **A, t_stack **B);
void	ft_move(t_stack **SRC, t_stack **DST);
void	ft_switch(t_stack **S);

int		ft_check_input(t_stack **stack);
int		ft_solve(t_stack **a, t_stack **b);

ssize_t	*error_status(void);
void	set_error(ssize_t error);
void	ft_exit_error(char *message);

#endif
