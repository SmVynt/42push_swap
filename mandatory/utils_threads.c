/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:34:48 by psmolin           #+#    #+#             */
/*   Updated: 2025/07/09 14:36:49 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*ft_think(void *argument)
{
	t_philo	*philo;

	philo = (t_philo *)argument;
	if (philo->id % 2 == 0)
		ft_sleep(philo->data->tte);
	while (1)
	{
		if (ft_someone_died(philo->data) == 1)
			break;
		pthread_mutex_lock(&philo->fork_1);
		pthread_mutex_lock(&philo->fork_2);
		ft_print_ts(philo->data, "is eating", philo->id, COLOR_GREEN);
		pthread_mutex_lock(&philo->lm_mutex);
		philo->last_meal = ft_get_time() - philo->data->start;
		pthread_mutex_unlock(&philo->lm_mutex);
		ft_sleep(philo->data->tte);
		pthread_mutex_unlock(&philo->fork_1);
		pthread_mutex_unlock(&philo->fork_2);
		if (ft_someone_died(philo->data) == 1)
			break;
		ft_print_ts(philo->data, "is sleeping", philo->id, COLOR_WHITE);
		ft_sleep(philo->data->tts);
		if (ft_someone_died(philo->data) == 1)
			break;
		ft_print_ts(philo->data, "is thinking", philo->id, COLOR_YELLOW);
		ft_sleep(philo->data->ttt);
	}
	return(NULL);
}

static void	*ft_doctor(void *argument)
{
	t_data	*data;
	long	cur_time;
	long	last_meal;
	int		i;

	data = (t_data *)argument;
	while (data->someone_died == 0)
	{
		cur_time = ft_get_time() - data->start;
		i = 0;
		while (i < data->philos_count)
		{
			pthread_mutex_lock(&data->philos[i].lm_mutex);
			last_meal = data->philos[i].last_meal;
			pthread_mutex_unlock(&data->philos[i].lm_mutex);
			if (cur_time - last_meal > data->ttd)
			{
				data->someone_died = 1;
				printf(COLOR_R"%ld %d died\n"COLOR_X, cur_time, data->philos[i].id);
			}
			i++;
		}
		usleep(DOCTOR_WAIT);
	}
	return (NULL);
}

void	ft_start_threads(t_data *data)
{
	int	i;

	i = 0;
	data->start = ft_get_time();
	while (i < data->philos_count)
	{
		pthread_create(&data->philos[i].thread, NULL, ft_think, &data->philos[i]);
		i++;
	}
	pthread_create(&data->doctor, NULL, ft_doctor, data);
}

void	ft_join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_count)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	pthread_join(data->doctor, NULL);
}

void	ft_cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_count)
	{
		pthread_mutex_destroy(&data->philos[i].lm_mutex);
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->mutex);
}
