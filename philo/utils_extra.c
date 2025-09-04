/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:35:05 by psmolin           #+#    #+#             */
/*   Updated: 2025/09/04 13:44:50 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_calc_init_wait(int ph_c, int id, t_data *data)
{
	long long	delta_time;
	int			k;

	if (ph_c <= 1)
		return (0);
	if (ph_c % 2 == 0)
		return ((id % 2) * data->tteat);
	if ((data->tteat * data->ph_c) % data->ttdie != 0)
		k = (data->tteat * data->ph_c) / data->ttdie + 1;
	else
		k = (data->tteat * data->ph_c) / data->ttdie;
	delta_time = (k * data->ttdie - (data->tteat * data->ph_c))
		/ (data->ph_c - 1);
	return ((id * (data->tteat + delta_time)) % data->ttdie);
}

void	ft_kill_philo(t_data *data, int i)
{
	pthread_mutex_lock(&data->mutex);
	data->finished = 1;
	pthread_mutex_unlock(&data->mutex);
	ft_print_ts(data, "died", data->philos[i].id, COLOR_RED);
}

void	ft_finish_eating(t_data *data)
{
	pthread_mutex_lock(&data->mutex);
	printf(COLOR_G"All philosophers have eaten required meals\n"COLOR_X);
	data->finished = 1;
	pthread_mutex_unlock(&data->mutex);
}

/**
 * @brief Function that frees allocated memory in the data structure.
 */
void	ft_free_data(t_data *data)
{
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
}

/**
 * @brief Function that prints an error message, frees allocated memory,
 * and exits the program.
 */
void	ft_exit_error(char *message, t_data *data)
{
	printf(COLOR_R "Error\n" COLOR_Y);
	printf("%s\n" COLOR_X, message);
	ft_free_data(data);
	exit (EXIT_FAILURE);
}
