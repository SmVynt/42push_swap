/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:35:05 by psmolin           #+#    #+#             */
/*   Updated: 2025/08/31 18:47:15 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

/**
* @brief Function that stores error status
*
* @return Returns a pointer to the error value.
**/
t_data	*ft_get_data(void)
{
	static t_data	data;

	return (&data);
}

/**
 * @brief Function that frees allocated memory in the data structure.
 */
void	ft_free_data(void)
{
	t_data	*data;

	data = ft_get_data();
	if (data->pid)
		free(data->pid);
}

/**
 * @brief Function that prints an error message, frees allocated memory,
 * and exits the program.
 */
void	ft_exit_error(char *message, t_data *data)
{
	printf(COLOR_R "Error\n" COLOR_Y);
	printf("%s\n" COLOR_X, message);
	ft_free_data();
	exit (EXIT_FAILURE);
}

void ft_clear_exit(int exit_code)
{
	ft_free_data();
	exit(exit_code);
}
