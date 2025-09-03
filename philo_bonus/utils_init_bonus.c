/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:34:59 by psmolin           #+#    #+#             */
/*   Updated: 2025/08/31 18:51:06 by psmolin          ###   ########.fr       */
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
	data->philos_count = ft_read_number(argv[1]);
	if (data->philos_count < 1)
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
	data->forks = NULL;
	ft_read_args(argc, argv, data);
	data->finished = 0;
	if (data->philos_count > MAX_PHILOS)
		ft_exit_error("Too many philosophers.", data);
	data->ttthink = data->ttdie - (data->tteat + data->ttsleep + THRESHOLD);
	if (data->ttthink < 0)
		data->ttthink = 0;
	data->pid = malloc(sizeof(pid_t) * data->philos_count);
	if (!data->forks || !data->pid)
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
	int		i;
	pid_t	pid;

	ft_init_data(argc, argv, data);
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/finished");
	data->forks = sem_open("/forks", O_CREAT | O_EXCL, 0644, data->philos_count);
	data->print = sem_open("/print", O_CREAT | O_EXCL, 0644, 1);
	data->finished = sem_open("/finished", O_CREAT | O_EXCL, 0644, 0);
	if (data->forks == SEM_FAILED || data->print == SEM_FAILED || data->finished == SEM_FAILED)
		ft_exit_error("Failed to create semaphores.", data);
	data->start = ft_get_time();
	i = 0;
	while (i < data->philos_count)
	{
		pid = fork();
		if (pid == 0)
		{
			ft_philo_process(data, i);
			ft_clean_exit(0);
		}
		else if (pid > 0)
			data->pid[i] = pid;
		else
			ft_exit_error("Fork failed.", data);
		i++;
	}
}

/**
 * @brief Clean exit function for child processes
 * @param status Exit status
 */
void	ft_clean_exit(int status)
{
	t_data	*data;

	data = ft_get_data();
	sem_close(data->forks);
	sem_close(data->print);
	sem_close(data->finished);
	exit(status);
}

/**
 * @brief Monitor child processes and handle death/completion
 * @param data The data structure
 */
void	ft_doctor(t_data *data)
{
	int		status;
	int		finished_count;
	pid_t	died_pid;

	finished_count = 0;

	while (1)
	{
		if (data->times_must_eat != -1)
		{
			while (sem_trywait(data->finished) == 0)
			{
				finished_count++;
				if (finished_count >= data->philos_count)
				{
					printf("All philosophers have finished eating!\n");
					ft_kill_all(data);
					return;
				}
			}
		}

		// Check if any process died
		died_pid = waitpid(-1, &status, WNOHANG);
		if (died_pid > 0)
		{
			// A process ended - kill all others
			if (WEXITSTATUS(status) == 1)
			{
				// Death occurred
				ft_kill_all(data);
				return;
			}
		}

		usleep(1000);  // Small delay
	}
}

/**
 * @brief Kill all philosopher processes
 * @param data The data structure
 */
void	ft_kill_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_count)
	{
		kill(data->pid[i], SIGTERM);
		i++;
	}
	i = 0;
	while (i < data->philos_count)
	{
		waitpid(data->pid[i], NULL, 0);
		i++;
	}
}
