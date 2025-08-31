/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lib.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:35:02 by psmolin           #+#    #+#             */
/*   Updated: 2025/08/31 13:58:08 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <time.h>

void	ft_sleep(int time)
{
	long	start;

	start = ft_get_time();
	while (ft_get_time() - start < time)
		usleep(500);
}

void	ft_print_ts(t_data *data, char *msg, int id, int color)
{
	long	cur_time;

	cur_time = ft_get_time() - data->start;
	pthread_mutex_lock(&data->mutex);
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
	pthread_mutex_unlock(&data->mutex);
}

int	ft_isfinished(t_data *data)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&data->mutex);
	if (data->finished == 1)
		ret = 1;
	pthread_mutex_unlock(&data->mutex);
	return (ret);
}

// long	ft_get_time(void)
// {
// 	struct timeval	tv;

// 	if (gettimeofday(&tv, NULL) == -1)
// 		return (set_error(1), 0);
// 	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
// }

long	ft_get_time(void)
{
	struct timespec	ts;

	if (clock_gettime(CLOCK_MONOTONIC, &ts) == -1)
		return (set_error(1), 0);
	return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}
