/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:34:59 by psmolin           #+#    #+#             */
/*   Updated: 2025/09/08 13:31:34 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

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
	data->pids = NULL;
	data->forks = NULL;
	data->print = NULL;
	data->finished = NULL;
	data->death = NULL;
	ft_read_args(argc, argv, data);
	data->pids = malloc(sizeof(pid_t) * data->ph_c);
	data->ttthink = data->ttdie - (data->tteat + data->ttsleep + THRESHOLD);
	if (data->ttthink < 0)
		data->ttthink = 0;
	if (!data->pids)
		ft_exit_error("Malloc failed.", data);
}

/**
 * @brief Function that initializes semaphores for process communication.
 * @param argc The number of command line arguments.
 * @param argv The command line arguments.
 * @param data The data structure to initialize.
 */
void	ft_initialize(int argc, char **argv, t_data *data)
{
	ft_init_data(argc, argv, data);
	sem_unlink("/philo_forks");
	sem_unlink("/philo_print");
	sem_unlink("/philo_finished");
	sem_unlink("/philo_death");
	data->forks = sem_open("/philo_forks", O_CREAT | O_EXCL, 0644, data->ph_c);
	data->print = sem_open("/philo_print", O_CREAT | O_EXCL, 0644, 1);
	data->finished = sem_open("/philo_finished", O_CREAT | O_EXCL, 0644, 0);
	data->death = sem_open("/philo_death", O_CREAT | O_EXCL, 0644, 0);
	if (data->forks == SEM_FAILED || data->print == SEM_FAILED
		|| data->finished == SEM_FAILED || data->death == SEM_FAILED)
		ft_exit_error("Failed to create semaphores.", data);
}
