/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:34:48 by psmolin           #+#    #+#             */
/*   Updated: 2025/08/31 16:08:24 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*ft_live(void *argument)
{
	t_philo	*philo;

	philo = (t_philo *)argument;
	if (philo->id % 2 == 0)
		ft_sleep(philo->data->tteat);
	while (ft_isfinished(philo->data) == 0)
	{
		pthread_mutex_lock(&philo->fork_1);
		pthread_mutex_lock(&philo->fork_2);
		ft_print_ts(philo->data, "has taken a fork", philo->id, COLOR_CYAN);
		ft_print_ts(philo->data, "is eating", philo->id, COLOR_GREEN);
		pthread_mutex_lock(&philo->lm_mutex);
		philo->last_meal_time = ft_get_time() - philo->data->start;
		pthread_mutex_unlock(&philo->lm_mutex);
		ft_sleep(philo->data->tteat);
		pthread_mutex_unlock(&philo->fork_1);
		pthread_mutex_unlock(&philo->fork_2);
		if (philo->meals_needed != -1)
		{
			pthread_mutex_lock(&philo->fe_mutex);
			philo->meals_had++;
			if (philo->meals_had >= philo->meals_needed)
				philo->finished_eating = 1;
			pthread_mutex_unlock(&philo->fe_mutex);
		}
		if (ft_isfinished(philo->data) == 1)
			break ;
		ft_print_ts(philo->data, "is sleeping", philo->id, COLOR_WHITE);
		ft_sleep(philo->data->ttsleep);
		if (ft_isfinished(philo->data) == 1)
			break ;
		ft_print_ts(philo->data, "is thinking", philo->id, COLOR_YELLOW);
		ft_sleep(philo->data->ttthink);
	}
	return (NULL);
}

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
		while (i < data->philos_count)
		{
			pthread_mutex_lock(&data->philos[i].lm_mutex);
			last_meal = data->philos[i].last_meal_time;
			pthread_mutex_unlock(&data->philos[i].lm_mutex);
			if (cur_time - last_meal > data->ttdie)
			{
				pthread_mutex_lock(&data->mutex);
				data->finished = 1;
				pthread_mutex_unlock(&data->mutex);
				ft_print_ts(data, "died", data->philos[i].id, COLOR_RED);
				return (NULL);
			}
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
		while (i < data->philos_count)
		{
			pthread_mutex_lock(&data->philos[i].fe_mutex);
			if (data->philos[i].finished_eating == 0)
				finished_eating = 0;
			pthread_mutex_unlock(&data->philos[i].fe_mutex);
			i++;
		}
		if (finished_eating == 1)
		{
			printf(COLOR_R"All philosophers have eaten required meals\n"COLOR_X);
			pthread_mutex_lock(&data->mutex);
			data->finished = 1;
			pthread_mutex_unlock(&data->mutex);
			return (NULL);
		}
		usleep(WAITER_WAIT);
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
		pthread_create(&data->philos[i].thread, NULL, ft_live, &data->philos[i]);
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
	while (i < data->philos_count)
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
	while (i < data->philos_count)
	{
		pthread_mutex_destroy(&data->philos[i].lm_mutex);
		pthread_mutex_destroy(&data->philos[i].fe_mutex);
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->mutex);
}
