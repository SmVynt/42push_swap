/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:35:05 by psmolin           #+#    #+#             */
/*   Updated: 2025/09/08 14:41:47 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

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

/**
 * @brief Clean exit function for child processes
 */
void	ft_clean_exit(t_data *data, int exit_code)
{
	if (data)
	{
		if (data->forks)
			sem_close(data->forks);
		if (data->print)
			sem_close(data->print);
		if (data->finished)
			sem_close(data->finished);
		if (data->death)
			sem_close(data->death);
		if (data->pids)
			free(data->pids);
	}
	exit(exit_code);
}

/**
 * @brief Signal handler for clean exit
 */
void	signal_handler(int sig)
{
	sem_t	*forks;
	sem_t	*print;
	sem_t	*finished;
	sem_t	*death;

	(void)sig;
	forks = sem_open("/philo_forks", 0);
	if (forks != SEM_FAILED)
		sem_close(forks);
	print = sem_open("/philo_print", 0);
	if (print != SEM_FAILED)
		sem_close(print);
	finished = sem_open("/philo_finished", 0);
	if (finished != SEM_FAILED)
		sem_close(finished);
	death = sem_open("/philo_death", 0);
	if (death != SEM_FAILED)
		sem_close(death);
	exit(0);
}

/**
 * @brief Cleanup semaphores and resources
 */
void	ft_free_data(t_data *data)
{
	if (data->forks)
	{
		sem_close(data->forks);
		sem_unlink("/philo_forks");
	}
	if (data->print)
	{
		sem_close(data->print);
		sem_unlink("/philo_print");
	}
	if (data->finished)
	{
		sem_close(data->finished);
		sem_unlink("/philo_finished");
	}
	if (data->death)
	{
		sem_close(data->death);
		sem_unlink("/philo_death");
	}
	if (data->pids)
		free(data->pids);
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
