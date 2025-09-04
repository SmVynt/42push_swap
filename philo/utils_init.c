/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:34:59 by psmolin           #+#    #+#             */
/*   Updated: 2025/09/04 13:39:52 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief Function that reads a number from a string.
 *
 * This function reads a number from the given string and returns it.
 * If the string is not a valid number, it returns -1.
 * @param str The string to read the number from.
 * @return The read number, or -1 on error.
 */
static int	ft_read_number(char *str)
{
	long long	num;
	int			sign;
	ssize_t		i;

	num = 0;
	sign = 1;
	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
			|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f'))
		i++;
	while (str[i] && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i++] == '-')
			sign *= -1;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i++] - '0');
		if (num > INT_MAX || num < INT_MIN)
			return (-1);
	}
	if (sign < 0 || str[i] != '\0')
		return (-1);
	return ((int)num);
}

/**
 * @brief Function that reads and validates command line arguments.
 * This function reads the command line arguments and validates them.
 * If any argument is invalid, it calls ft_exit_error to print an error
 * message and exit the program.
 * @param argc The number of command line arguments.
 * @param argv The command line arguments.
 * @param data The data structure to store the read values.
 */
static void	ft_read_args(int argc, char **argv, t_data *data)
{
	if (argc < 5 || argc > 6)
		ft_exit_error("Invalid number of arguments. Expected \
4 or 5 arguments.", data);
	data->ph_c = ft_read_number(argv[1]);
	if (data->ph_c < 1)
		ft_exit_error("Number of philosophers must be at least 1.", data);
	data->ttdie = ft_read_number(argv[2]);
	if (data->ttdie < 1)
		ft_exit_error("Time to die must be a positive integer.", data);
	data->tteat = ft_read_number(argv[3]);
	if (data->tteat < 1)
		ft_exit_error("Time to eat must be a positive integer.", data);
	data->ttsleep = ft_read_number(argv[4]);
	if (data->ttsleep < 1)
		ft_exit_error("Time to sleep must be a positive integer.", data);
	data->times_must_eat = -1;
	if (argc == 6)
		data->times_must_eat = ft_read_number(argv[5]);
	if (argc == 6 && data->times_must_eat < 1)
		ft_exit_error("Number of times each philosopher must eat \
must be a positive integer.", data);
}

/**
 * @brief Function that initializes the data structure.
 * This function initializes the data structure by reading the command line
 * arguments and allocating memory for the philosophers and forks.
 * If any allocation fails, it calls ft_exit_error to print an error message
 * and exit the program.
 * @param argc The number of command line arguments.
 * @param argv The command line arguments.
 * @param data The data structure to initialize.
 */
static void	ft_init_data(int argc, char **argv, t_data *data)
{
	data->philos = NULL;
	data->forks = NULL;
	ft_read_args(argc, argv, data);
	data->finished = 0;
	data->philos = malloc(sizeof(t_philo) * data->ph_c);
	data->forks = malloc(sizeof(t_mutex) * data->ph_c);
	data->ttthink = data->ttdie - (data->tteat + data->ttsleep + THRESHOLD);
	if (data->ttthink < 0)
		data->ttthink = 0;
	if (!data->forks || !data->philos)
		ft_exit_error("Malloc failed.", data);
}

/**
 * @brief Function that initializes the philosophers and forks.
 * This function initializes the philosophers and forks by setting their
 * initial values and initializing the mutexes.
 * @param argc The number of command line arguments.
 * @param argv The command line arguments.
 * @param data The data structure to initialize.
 */
void	ft_initialize(int argc, char **argv, t_data *data)
{
	int	i;

	ft_init_data(argc, argv, data);
	pthread_mutex_init(&data->mutex, NULL);
	i = 0;
	while (i < data->ph_c)
		pthread_mutex_init(&data->forks[i++], NULL);
	i = -1;
	while (++i < data->ph_c)
	{
		data->philos[i].id = i + 1;
		data->philos[i].fork_1 = &data->forks[i];
		data->philos[i].fork_2 = &data->forks[(i + 1) % data->ph_c];
		data->philos[i].data = data;
		data->philos[i].meals_had = 0;
		data->philos[i].finished_eating = 0;
		data->philos[i].meals_needed = data->times_must_eat;
		data->philos[i].last_meal_time = 0;
		data->philos[i].time_to_wait = ft_calc_init_wait(data->ph_c, i, data);
		pthread_mutex_init(&data->philos[i].lm_mutex, NULL);
		pthread_mutex_init(&data->philos[i].fe_mutex, NULL);
	}
}
