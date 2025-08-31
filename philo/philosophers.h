/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 21:38:54 by psmolin           #+#    #+#             */
/*   Updated: 2025/08/31 15:58:45 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
// # include <linux/time.h>

# define COLOR_R "\033[31m"
# define COLOR_G "\033[32m"
# define COLOR_Y "\033[33m"
# define COLOR_B "\033[34m"
# define COLOR_M "\033[35m"
# define COLOR_C "\033[36m"
# define COLOR_W "\033[37m"
# define COLOR_X "\033[0m"

# define COLOR_GREEN	0
# define COLOR_YELLOW	1
# define COLOR_RED		2
# define COLOR_WHITE	3
# define COLOR_CYAN		4

# define DOCTOR_WAIT 5000
# define WAITER_WAIT 5000
# define THRESHOLD 10

typedef pthread_t		t_pth;
typedef pthread_mutex_t	t_mutex;
typedef struct s_data	t_data;

typedef struct s_philo
{
	int		id;
	long	last_meal_time;
	t_mutex	lm_mutex;
	int		meals_had;
	int		meals_needed;
	int		finished_eating;
	t_mutex	fe_mutex;
	t_pth	thread;
	t_mutex	fork_1;
	t_mutex	fork_2;
	t_data	*data;
}	t_philo;

struct s_data
{
	int		philos_count;
	t_philo	*philos;
	t_mutex	*forks;
	int		ttdie;
	int		tteat;
	int		ttsleep;
	int		ttthink;
	t_pth	doctor;
	t_pth	waiter;
	int		finished;
	int		finished_eating;
	t_mutex	mutex;
	int		times_must_eat;
	long	start;
};

void	ft_initialize(int argc, char **argv, t_data *data);
void	ft_start_threads(t_data *data);
void	ft_join_threads(t_data *data);
void	ft_cleanup(t_data *data);

void	ft_sleep(int time);
long	ft_get_time(void);
void	ft_print_ts(t_data *data, char *msg, int id, int color);
int		ft_isfinished(t_data *data);

ssize_t	*error_status(void);
void	ft_free_data(t_data *data);
void	set_error(ssize_t error);
void	ft_exit_error(char *message, t_data *data);

#endif
