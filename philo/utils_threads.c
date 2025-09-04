/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:34:48 by psmolin           #+#    #+#             */
/*   Updated: 2025/09/04 12:13:58 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*ft_doctor(void *argument)
{
	t_data	*data;
	long	cur_time;
	long	last_meal;
	int		i;

	data = (t_data *)argument;
	while (ft_isfinished(data) == 0)
	{
		cur_time = ft_get_time() - data->start;
		i = 0;
		while (i < data->ph_c)
		{
			pthread_mutex_lock(&data->philos[i].lm_mutex);
			last_meal = data->philos[i].last_meal_time;
			pthread_mutex_unlock(&data->philos[i].lm_mutex);
			if (cur_time - last_meal > data->ttdie)
				return (ft_kill_philo(data, i), NULL);
			i++;
		}
		usleep(DOCTOR_WAIT);
	}
	return (NULL);
}

static void	*ft_waiter(void *argument)
{
	t_data	*data;
	long	finished_eating;
	int		i;

	data = (t_data *)argument;
	while (ft_isfinished(data) == 0)
	{
		i = 0;
		finished_eating = 1;
		while (i < data->ph_c)
		{
			pthread_mutex_lock(&data->philos[i].fe_mutex);
			if (data->philos[i].finished_eating == 0)
				finished_eating = 0;
			pthread_mutex_unlock(&data->philos[i].fe_mutex);
			i++;
		}
		if (finished_eating == 1)
			return (ft_finish_eating(data), NULL);
		usleep(WAITER_WAIT);
	}
	return (NULL);
}

void	ft_start_threads(t_data *data)
{
	int	i;

	i = 0;
	data->start = ft_get_time();
	while (i < data->ph_c)
	{
		pthread_create(&data->philos[i].thread, NULL, ft_live,
			&data->philos[i]);
		i++;
	}
	pthread_create(&data->doctor, NULL, ft_doctor, data);
	if (data->times_must_eat != -1)
		pthread_create(&data->waiter, NULL, ft_waiter, data);
}

void	ft_join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->ph_c)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	pthread_join(data->doctor, NULL);
	if (data->times_must_eat != -1)
		pthread_join(data->waiter, NULL);
}

void	ft_cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->ph_c)
	{
		pthread_mutex_destroy(&data->philos[i].lm_mutex);
		pthread_mutex_destroy(&data->philos[i].fe_mutex);
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->mutex);
}
