/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:34:48 by psmolin           #+#    #+#             */
/*   Updated: 2025/09/03 13:58:51 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

/**
 * @brief Check if philosopher should die or simulation should end
 * @param philo The philosopher to check
 * @return 1 if should exit, 0 if should continue
 */
static int	check_death(t_philo *philo)
{
	long	current_time;
	long	time_since_last_meal;

	current_time = ft_get_time() - philo->data->start;
	time_since_last_meal = current_time - philo->last_meal_time;
	if (time_since_last_meal > philo->data->ttdie)
	{
		ft_print_ts(philo->data, "died", philo->id, COLOR_RED);
		// Signal parent process about death
		kill(getppid(), SIGUSR1);
		exit(1);
	}
	return (0);
}

static void ft_philo_init(t_philo *philo, t_data *data, int index)
{
	philo->id = index + 1;
	philo->last_meal_time = 0;
	philo->meals_needed = data->times_must_eat;
	philo->meals_had = 0;
	philo->finished_eating = 0;
	philo->data = data;
}

void ft_philo_process(t_data *data, int index)
{
	t_philo	philo;

	ft_philo_init(&philo, data, index);
	if (philo.id % 2 == 0)
		ft_sleep(philo.data->tteat);
	while (1)
	{
		if (check_death(&philo))
			break ;
		sem_wait(data->forks);
		sem_wait(data->forks);
		ft_print_ts(data, "has taken a fork", philo.id, COLOR_CYAN);
		ft_print_ts(data, "is eating", philo.id, COLOR_GREEN);
		philo.last_meal_time = ft_get_time() - data->start;
		ft_sleep(data->tteat);
		if (check_death(&philo))
			break ;
		philo.meals_had++;
		if (data->times_must_eat != -1 && philo.meals_had >= data->times_must_eat)
			sem_post(data->finished);
		sem_post(data->forks);
		sem_post(data->forks);
		if (check_death(&philo))
			break ;
		ft_print_ts(data, "is sleeping", philo.id, COLOR_WHITE);
		ft_sleep(data->ttsleep);
		if (check_death(&philo))
			break ;
		ft_print_ts(data, "is thinking", philo.id, COLOR_YELLOW);
		ft_sleep(data->ttthink);
	}
}

void	ft_cleanup(t_data *data)
{
	// int	i;

	// i = 0;
	(void)data;
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/finished");
	// while (i < data->philos_count)
	// {
	// 	pthread_mutex_destroy(&data->philos[i].lm_mutex);
	// 	pthread_mutex_destroy(&data->philos[i].fe_mutex);
	// 	pthread_mutex_destroy(&data->forks[i]);
	// 	i++;
	// }
	// pthread_mutex_destroy(&data->mutex);
}
