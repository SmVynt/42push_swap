/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 21:38:54 by psmolin           #+#    #+#             */
/*   Updated: 2025/09/04 12:21:37 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <sys/time.h>
# include <time.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>

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

# define DOCTOR_WAIT	5000
# define WAITER_WAIT	5000
# define THRESHOLD		10
# define MAX_PHILOS		32768

typedef struct s_data	t_data;

typedef struct s_philo
{
	int		id;
	long	last_meal_time;
	int		meals_had;
	int		meals_needed;
	int		finished_eating;
	t_data	*data;
}	t_philo;

struct s_data
{
	int		philos_count;
	pid_t	*pid;
	int		ttdie;
	int		tteat;
	int		ttsleep;
	int		ttthink;
	int		finished_eating;
	int		times_must_eat;
	long	start;
	int		is_finished;
	sem_t	*forks;
	sem_t	*finished;
	sem_t	*print;
};

void	ft_initialize(int argc, char **argv, t_data *data);
void	ft_start_threads(t_data *data);
void	ft_join_threads(t_data *data);
void	ft_cleanup(t_data *data);
void	ft_philo_process(t_data *data, int index);
void	ft_doctor(t_data *data);
void	ft_kill_all(t_data *data);

void	ft_sleep(int time);
long	ft_get_time(void);
void	ft_print_ts(t_data *data, char *msg, int id, int color);

int		ft_calculate_init_wait(int ph_c, int id, t_data *data);
t_data	*ft_get_data(void);
void	ft_free_data(void);
void	ft_exit_error(char *message, t_data *data);
void	ft_clean_exit(int status);

#endif
