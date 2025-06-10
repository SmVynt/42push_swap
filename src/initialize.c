/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:34:59 by psmolin           #+#    #+#             */
/*   Updated: 2025/06/10 15:02:04 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	ft_read_number(ssize_t *i, char *str, t_stacks *stacks)
{
	int			sign;
	long long	result;

	sign = 1;
	result = 0;
	if (str[*i] == '-')
	{
		sign = -1;
		(*i)++;
	}
	if (str[*i] == '+')
		(*i)++;
	if (str[*i] < '0' || str[*i] > '9')
		ft_exit_error("Not a number.", stacks);
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		result = result * 10 + (str[*i] - '0') * sign;
		if (result > INT_MAX || result < INT_MIN)
			ft_exit_error("Number is out of INT bounds.", stacks);
		(*i)++;
	}
	return ((int)result);
}

void	ft_read_args(int argc, char **argv, t_stacks *stacks)
{
	ssize_t	i;
	ssize_t	j;
	int		num;
	t_stack	*tmp;

	i = 0;
	while (++i < argc && !*error_status())
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] == '-' || (argv[i][j] >= '0' && argv[i][j] <= '9'))
			{
				num = ft_read_number(&j, argv[i], stacks);
				tmp = ft_add_new(num, stacks->a);
				stacks->size_a++;
				if (!tmp || !ft_add_back(stacks->a, tmp))
					return (set_error(1));
			}
			else if (argv[i][j] == ' ')
				j++;
			else
				return (set_error(1));
		}
	}
}
