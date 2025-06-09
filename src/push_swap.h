/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 21:38:54 by psmolin           #+#    #+#             */
/*   Updated: 2025/06/10 01:01:56 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>

# define COLOR_R "\033[31m"
# define COLOR_G "\033[32m"
# define COLOR_Y "\033[33m"
# define COLOR_B "\033[34m"
# define COLOR_M "\033[35m"
# define COLOR_C "\033[36m"
# define COLOR_W "\033[37m"
# define COLOR_X "\033[0m"

typedef struct s_stack	t_stack;
typedef struct s_stacks	t_stacks;

struct s_stack
{
	t_stack	**head;
	int		value_init;
	int		value;
	int		price;
	int		price_left;
	int		price_total;
	t_stack	*next;
	t_stack	*prev;
};

struct s_stacks
{
	t_stack	**a;
	int		size_a;
	t_stack	**b;
	int		size_b;
	int		complexity;
	int		max_value;
};

typedef struct s_prcs
{
	int	price_a;
	int	price_b;
}	t_prcs;

void	ft_read_args(int argc, char **argv, t_stacks *stacks);
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

int		ft_sa(t_stacks *stacks);
int		ft_sb(t_stacks *stacks);
int		ft_ss(t_stacks *stacks);
int		ft_pa(t_stacks *stacks);
int		ft_pb(t_stacks *stacks);
int		ft_ra(t_stacks *stacks);
int		ft_rb(t_stacks *stacks);
int		ft_rr(t_stacks *stacks);
int		ft_rra(t_stacks *stacks);
int		ft_rrb(t_stacks *stacks);
int		ft_rrr(t_stacks *stacks);

int		ft_check_input(t_stack **stack);
int		ft_solve(t_stacks *stacks);
t_prcs	ft_calculate_prices(t_stacks *stacks);
void	ft_move_cheapest(t_stacks *stacks, t_prcs prices);
int		ft_nearest_small(t_stacks *stacks, int val);

int		ft_print(char *str);
int		ft_num2n(int num, int n);
int		ft_num3n(int num, int n);

ssize_t	*error_status(void);
void	set_error(ssize_t error);
void	ft_exit_error(char *message, t_stacks *stacks);

#endif
