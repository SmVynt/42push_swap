/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:35:05 by psmolin           #+#    #+#             */
/*   Updated: 2025/06/08 13:41:09 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
* @brief Function that sets error status.
**/
void	set_error(ssize_t error)
{
	*error_status() = error;
}

/**
* @brief Function that stores error status
*
* @return Returns a pointer to the error value.
**/
ssize_t	*error_status(void)
{
	static ssize_t	status;

	return (&status);
}

void	ft_exit_error(char *message, t_stacks *stacks)
{
	ft_free(stacks->a);
	ft_free(stacks->b);
	ft_print(COLOR_R "Error\n" COLOR_Y);
	ft_print(message);
	ft_print("\n" COLOR_X);
	exit(1);
}
