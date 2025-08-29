/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:35:05 by psmolin           #+#    #+#             */
/*   Updated: 2025/07/07 19:57:16 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

void	ft_free_data(t_data *data)
{
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
}

void	ft_exit_error(char *message, t_data *data)
{
	printf(COLOR_R "Error\n" COLOR_Y);
	printf("%s\n" COLOR_X, message);
	ft_free_data(data);
	exit (EXIT_FAILURE);
}
