/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_checker_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:34:48 by psmolin           #+#    #+#             */
/*   Updated: 2025/06/10 15:14:54 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	ft_check_command(char *cmd)
{
	if (ft_strncmp(cmd, "sa\n", 3) == 0
		|| ft_strncmp(cmd, "sb\n", 3) == 0
		|| ft_strncmp(cmd, "ss\n", 3) == 0
		|| ft_strncmp(cmd, "pa\n", 3) == 0
		|| ft_strncmp(cmd, "pb\n", 3) == 0
		|| ft_strncmp(cmd, "ra\n", 3) == 0
		|| ft_strncmp(cmd, "rb\n", 3) == 0
		|| ft_strncmp(cmd, "rr\n", 3) == 0
		|| ft_strncmp(cmd, "rra\n", 4) == 0
		|| ft_strncmp(cmd, "rrb\n", 4) == 0
		|| ft_strncmp(cmd, "rrr\n", 4) == 0
	)
		return (0);
	return (1);
}

static void	ft_run_command_sub(char *cmd, t_stacks *stacks)
{
	if (ft_strncmp(cmd, "ra\n", 3) == 0)
		ft_roll_up(stacks->a);
	if (ft_strncmp(cmd, "rb\n", 3) == 0)
		ft_roll_up(stacks->b);
	if (ft_strncmp(cmd, "rr\n", 3) == 0)
		ft_roll_up(stacks->a);
	if (ft_strncmp(cmd, "rr\n", 3) == 0)
		ft_roll_up(stacks->b);
	if (ft_strncmp(cmd, "rra\n", 4) == 0)
		ft_roll_down(stacks->a);
	if (ft_strncmp(cmd, "rrb\n", 4) == 0)
		ft_roll_down(stacks->b);
	if (ft_strncmp(cmd, "rrr\n", 4) == 0)
		ft_roll_down(stacks->a);
	if (ft_strncmp(cmd, "rrr\n", 4) == 0)
		ft_roll_down(stacks->b);
}

static void	ft_run_command(char *cmd, t_stacks *stacks)
{
	if (ft_strncmp(cmd, "sa\n", 3) == 0)
		ft_switch(stacks->a);
	if (ft_strncmp(cmd, "sb\n", 3) == 0)
		ft_switch(stacks->b);
	if (ft_strncmp(cmd, "ss\n", 3) == 0)
		ft_switch(stacks->a);
	if (ft_strncmp(cmd, "ss\n", 3) == 0)
		ft_switch(stacks->b);
	if (ft_strncmp(cmd, "pa\n", 3) == 0)
		ft_move(stacks->b, stacks->a);
	if (ft_strncmp(cmd, "pb\n", 3) == 0)
		ft_move(stacks->a, stacks->b);
	ft_run_command_sub(cmd, stacks);
}

static void	ft_read_commands(t_stacks *stacks)
{
	char	*line;

	line = get_next_line(0);
	while (line != NULL && ft_strncmp(line, "\n", 1) != 0)
	{
		if (ft_check_command(line) == 1)
		{
			free(line);
			ft_exit_error("Wrong command entered.", stacks);
		}
		ft_run_command(line, stacks);
		free(line);
		line = get_next_line(0);
	}
	if (line)
		free(line);
}

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
	ft_read_commands(&stacks);
	ft_check_sort(&stacks);
	ft_free(stacks.a);
	ft_free(stacks.b);
	return (0);
}
