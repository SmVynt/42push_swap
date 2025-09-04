/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:34:48 by psmolin           #+#    #+#             */
/*   Updated: 2025/09/04 14:09:37 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
* Check if philosopher has eaten enough
*/
static void	ft_check_fullness(t_philo *philo)
{
	if (philo->meals_needed != -1)
	{
		pthread_mutex_lock(&philo->fe_mutex);
		philo->meals_had++;
		if (philo->meals_had >= philo->meals_needed)
			philo->finished_eating = 1;
		pthread_mutex_unlock(&philo->fe_mutex);
	}
}

/**
* Philosopher eating routine
* Returns -1 if simulation should end, 0 otherwise
*/
static int	ft_philo_eat(t_philo *philo)
{
	if (philo->data->ph_c == 1)
	{
		pthread_mutex_lock(philo->fork_1);
		if (ft_isfinished(philo->data) == 1)
			return (pthread_mutex_unlock(philo->fork_1), -1);
		ft_print_ts(philo->data, "has taken a fork", philo->id, COLOR_CYAN);
		return (pthread_mutex_unlock(philo->fork_1), -1);
	}
	pthread_mutex_lock(philo->fork_1);
	if (ft_isfinished(philo->data) == 1)
		return (pthread_mutex_unlock(philo->fork_1), -1);
	ft_print_ts(philo->data, "has taken a fork", philo->id, COLOR_CYAN);
	pthread_mutex_lock(philo->fork_2);
	if (ft_isfinished(philo->data) == 1)
		return (pthread_mutex_unlock(philo->fork_1),
			pthread_mutex_unlock(philo->fork_2), -1);
	ft_print_ts(philo->data, "has taken a fork", philo->id, COLOR_CYAN);
	ft_print_ts(philo->data, "is eating", philo->id, COLOR_GREEN);
	pthread_mutex_lock(&philo->lm_mutex);
	philo->last_meal_time = ft_get_time() - philo->data->start;
	pthread_mutex_unlock(&philo->lm_mutex);
	ft_sleep(philo->data->tteat);
	pthread_mutex_unlock(philo->fork_1);
	pthread_mutex_unlock(philo->fork_2);
	return (0);
}

static int	ft_philo_sleep(t_philo *philo)
{
	if (ft_isfinished(philo->data) == 1)
		return (-1);
	ft_print_ts(philo->data, "is sleeping", philo->id, COLOR_WHITE);
	ft_sleep(philo->data->ttsleep);
	return (0);
}

static int	ft_philo_think(t_philo *philo)
{
	if (ft_isfinished(philo->data) == 1)
		return (-1);
	ft_print_ts(philo->data, "is thinking", philo->id, COLOR_YELLOW);
	ft_sleep(philo->data->ttthink);
	return (0);
}

void	*ft_live(void *argument)
{
	t_philo	*philo;
	t_mutex	*temp_fork;

	philo = (t_philo *)argument;
	ft_sleep(philo->time_to_wait);
	if (philo->fork_2 < philo->fork_1)
	{
		temp_fork = philo->fork_1;
		philo->fork_1 = philo->fork_2;
		philo->fork_2 = temp_fork;
	}
	while (ft_isfinished(philo->data) == 0)
	{
		if (ft_philo_eat(philo) == -1)
			break ;
		ft_check_fullness(philo);
		if (ft_philo_sleep(philo) == -1)
			break ;
		if (ft_philo_think(philo) == -1)
			break ;
	}
	return (NULL);
}
