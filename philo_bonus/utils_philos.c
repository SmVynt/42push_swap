/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:34:48 by psmolin           #+#    #+#             */
/*   Updated: 2025/09/08 15:06:55 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	ft_check_death(t_philo *philo)
{
	if (ft_get_time() - philo->data->start - philo->last_meal_time
		> philo->data->ttdie)
	{
		sem_post(philo->data->death);
		ft_print_ts(philo->data, "died", philo->id, COLOR_RED);
		ft_clean_exit(philo->data, 1);
	}
}

/**
 * @brief Handle eating process for philosopher
 */
static void	ft_eat(t_philo *philo, t_data *data)
{
	sem_wait(data->forks);
	ft_check_death(philo);
	ft_print_ts(data, "has taken a fork", philo->id, COLOR_CYAN);
	sem_wait(data->forks);
	ft_check_death(philo);
	ft_print_ts(data, "has taken a fork", philo->id, COLOR_CYAN);
	ft_print_ts(data, "is eating", philo->id, COLOR_GREEN);
	philo->last_meal_time = ft_get_time() - data->start;
	ft_sleep(data->tteat);
	philo->meals_had++;
	if (data->times_must_eat != -1 && philo->meals_had >= data->times_must_eat)
	{
		sem_post(data->forks);
		sem_post(data->forks);
		ft_clean_exit(data, 0);
	}
	sem_post(data->forks);
	sem_post(data->forks);
}

/**
 * @brief Individual philosopher process routine
 */
void	ft_philosopher_process(t_data *data, int index)
{
	t_philo	philo;

	signal(SIGTERM, signal_handler);
	signal(SIGINT, signal_handler);
	philo.id = index + 1;
	philo.last_meal_time = 0;
	philo.meals_needed = data->times_must_eat;
	philo.meals_had = 0;
	philo.finished_eating = 0;
	philo.data = data;
	ft_sleep(ft_calc_init_wait(data->ph_c, index, data));
	while (1)
	{
		ft_check_death(&philo);
		ft_eat(&philo, data);
		ft_print_ts(data, "is sleeping", philo.id, COLOR_WHITE);
		ft_sleep(data->ttsleep);
		ft_check_death(&philo);
		ft_print_ts(data, "is thinking", philo.id, COLOR_YELLOW);
		ft_sleep(data->ttthink);
	}
}
