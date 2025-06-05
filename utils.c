/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:35:05 by psmolin           #+#    #+#             */
/*   Updated: 2025/05/15 16:02:40 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
* @brief Function that sets error status.
**/
void	set_error(ssize_t error)
{
	ssize_t	*status;

	status = error_status();
	*status = error;
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

void	ft_exit_error(char *message, t_stack *a, t_stack *b)
{
	ft_free(a);
	ft_free(b);
	printf("Error\n");
	printf("%s\n", message);
	exit(1);
}
