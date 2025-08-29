/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:34:59 by psmolin           #+#    #+#             */
/*   Updated: 2025/07/09 14:54:46 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

static void	ft_read_args(int argc, char **argv, t_data *data)
{
	if (argc < 5 || argc > 6)
		ft_exit_error("Invalid number of arguments. Expected \
			4 or 5 arguments.", data);
	data->philos_count = ft_read_number(argv[1]);
	if (data->philos_count < 1)
		ft_exit_error("Number of philosophers must be at least 1.", data);
	data->ttd = ft_read_number(argv[2]);
	if (data->ttd < 1)
		ft_exit_error("Time to die must be a positive integer.", data);
	data->tte = ft_read_number(argv[3]);
	if (data->tte < 1)
		ft_exit_error("Time to eat must be a positive integer.", data);
	data->tts = ft_read_number(argv[4]);
	if (data->tts < 1)
		ft_exit_error("Time to sleep must be a positive integer.", data);
	data->to_eat = -1;
	if (argc == 6)
		data->to_eat = ft_read_number(argv[5]);
	if (argc == 6 && data->to_eat < 1)
		ft_exit_error("Number of times each philosopher must eat \
			must be a positive integer", data);
}

static void	ft_init_data(int argc, char **argv, t_data *data)
{
	data->philos = NULL;
	data->forks = NULL;
	ft_read_args(argc, argv, data);
	data->someone_died = 0;
	data->philos = malloc(sizeof(t_philo) * data->philos_count);
	data->forks = malloc(sizeof(t_mutex) * data->philos_count);
	data->ttt = data->ttd - (data->tte + data->tts + THRESHOLD);
	if (data->ttt < 0)
		data->ttt = 0;
	if (!data->forks || !data->philos)
		ft_exit_error("Malloc failed", data);
}

void	ft_initialize(int argc, char **argv, t_data *data)
{
	int	i;

	ft_init_data(argc, argv, data);
	pthread_mutex_init(&data->mutex, NULL);
	i = 0;
	while (i < data->philos_count)
		pthread_mutex_init(&data->forks[i++], NULL);
	i = 0;
	while (i < data->philos_count)
	{
		data->philos[i].id = i + 1;
		data->philos[i].last_meal = 0;
		data->philos[i].fork_1 = data->forks[i];
		data->philos[i].fork_2 = data->forks[(i + 1) % data->philos_count];
		data->philos[i].meals_count = 0;
		data->philos[i].data = data;
		pthread_mutex_init(&data->philos[i].lm_mutex, NULL);
		i++;
	}
}
