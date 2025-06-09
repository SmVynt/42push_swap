/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:34:59 by psmolin           #+#    #+#             */
/*   Updated: 2025/06/10 00:17:37 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	ft_read_number(ssize_t *i, char *str)
{
	int			sign;
	ssize_t		j;
	long long	result;

	sign = 1;
	result = 0;
	j = *i;
	if (str[j] == '-')
	{
		sign = -1;
		j++;
	}
	if (str[j] < '0' || str[j] > '9')
		return (set_error(1), 0);
	while (str[j] >= '0' && str[j] <= '9')
	{
		result = result * 10 + (str[j] - '0') * sign;
		if (result > INT_MAX || result < INT_MIN)
			return (set_error(1), 0);
		j++;
	}
	*i = j;
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
				num = ft_read_number(&j, argv[i]);
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
