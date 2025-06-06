/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:34:59 by psmolin           #+#    #+#             */
/*   Updated: 2025/06/06 11:06:43 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	ft_read_number(ssize_t *i, char *str)
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
	if (str[*i] <= '0' || str[*i] > '9')
		return (set_error(1), 0);
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		result = result * 10 + (str[*i] - '0') * sign;
		if (result > INT_MAX || result < INT_MIN)
			return (set_error(1), 0);
		(*i)++;
	}
	return ((int)result);
}

void	ft_read_args(int argc, char **argv, t_stack **A)
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
				tmp = ft_add_new(num, A);
				if (!tmp || !ft_add_back(A, tmp))
					return (set_error(1));
			}
			else if (argv[i][j] == ' ')
				j++;
			else
				return (set_error(1));
		}
	}
}
