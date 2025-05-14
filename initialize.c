/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:34:59 by psmolin           #+#    #+#             */
/*   Updated: 2025/05/14 21:51:32 by psmolin          ###   ########.fr       */
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
			printf("%ld\n", i);
			if (argv[i][j] == '-' || (argv[i][j] >= '0' && argv[i][j] <= '9'))
			{
				num = ft_read_number(&j, argv[i]);
				tmp = ft_add_new(num, A);
				if (!tmp || !ft_add_back(A, tmp))
					return (set_error(1), ft_free(A));
			}
			else if (argv[i][j] == ' ')
				j++;
			else
				return (set_error(1), ft_free(A));
		}
	}
}

void	ft_print_stack(t_stack **stack)
{
	t_stack	*tmp;

	if (!stack || !*stack)
	{
		printf("\n");
		return ;
	}
	tmp = *stack;
	while (tmp)
	{
		printf("%d ", tmp->value_init);
		tmp = tmp->next;
		if (tmp == *stack)
			break ;
	}
	printf("\n");
}
