/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lib.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:35:02 by psmolin           #+#    #+#             */
/*   Updated: 2025/09/08 15:07:13 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

/**
 * Sleep for a specified amount of time in milliseconds.
 */
void	ft_sleep(int time)
{
	long	start;

	start = ft_get_time();
	while (ft_get_time() - start < time)
		usleep(500);
}

/**
 * Print a timestamped message using semaphore for synchronization.
 */
void	ft_print_ts(t_data *data, char *msg, int id, int color)
{
	long	cur_time;

	cur_time = ft_get_time() - data->start;
	sem_wait(data->print);
	if (color == COLOR_GREEN)
		printf(COLOR_G);
	else if (color == COLOR_YELLOW)
		printf(COLOR_Y);
	else if (color == COLOR_RED)
		printf(COLOR_R);
	else if (color == COLOR_WHITE)
		printf(COLOR_W);
	else if (color == COLOR_CYAN)
		printf(COLOR_C);
	else
		printf(COLOR_X);
	printf("%ld %d %s\n" COLOR_X, cur_time, id, msg);
	sem_post(data->print);
}

/**
 * Check if the simulation is finished.
 */
// int	ft_isfinished(t_data *data)
// {
// 	int	ret;

// 	ret = 0;
// 	pthread_mutex_lock(&data->mutex);
// 	if (data->finished == 1)
// 		ret = 1;
// 	pthread_mutex_unlock(&data->mutex);
// 	return (ret);
// }

/**
 * Get the current time in milliseconds.
 */
long	ft_get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
