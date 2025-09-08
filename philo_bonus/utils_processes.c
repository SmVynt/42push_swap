/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:34:48 by psmolin           #+#    #+#             */
/*   Updated: 2025/09/08 15:07:24 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

/**
 * @brief Start all philosopher processes
 */
void	ft_start_processes(t_data *data)
{
	int		i;
	pid_t	pid;

	data->start = ft_get_time();
	i = 0;
	while (i < data->ph_c)
	{
		pid = fork();
		if (pid == 0)
		{
			ft_philosopher_process(data, i);
			exit(0);
		}
		else if (pid > 0)
			data->pids[i] = pid;
		else
			ft_exit_error("Fork failed", data);
		i++;
	}
}

/**
 * @brief Wait for all processes and monitor completion
 */
int	ft_wait_processes(t_data *data)
{
	int		status;
	int		finished_count;
	pid_t	died_pid;

	finished_count = 0;
	while (1)
	{
		died_pid = waitpid(-1, &status, WNOHANG);
		if (died_pid > 0)
		{
			if (WEXITSTATUS(status) == 1)
				return (ft_kill_all_processes(data), 1);
			else if (WEXITSTATUS(status) == 0 && data->times_must_eat != -1)
			{
				finished_count++;
				if (finished_count >= data->ph_c)
				{
					printf(COLOR_G"All philosophers have finished eating!\n"
						COLOR_X);
					return (0);
				}
			}
		}
		usleep(DOCTOR_WAIT);
	}
}

/**
 * @brief Kill all philosopher processes
 */
void	ft_kill_all_processes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->ph_c)
	{
		kill(data->pids[i], SIGTERM);
		i++;
	}
	i = 0;
	while (i < data->ph_c)
	{
		waitpid(data->pids[i], NULL, 0);
		i++;
	}
}
