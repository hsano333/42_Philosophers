/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 22:59:19 by hsano             #+#    #+#             */
/*   Updated: 2022/10/05 04:00:09 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <sys/fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include <unistd.h>
# include <semaphore.h>
# include <signal.h>

enum	e_strs {
	THINK,
	FORKS,
	EAT,
	SLEEP,
	DIE
};

typedef struct timeval	t_time;
typedef struct s_man
{
	int				id;
	pid_t			pid;
	pid_t			n_pid;
	size_t			cnt_eat;
	t_time			timestamp_eating;
	pthread_t		thread;
	void			*philos;
}	t_man;

typedef struct s_philos
{
	int				num;
	int				time_die;
	int				time_eat;
	int				time_slp;
	int				must_eat_num;
	int				end_flag;
	pid_t			np_pid;
	pid_t			pp_pid;
	t_man			*mans;
	t_time			boot_time;
	char			*sem_name;
	sem_t			*sem_fd;
	char			*sem_put_name;
	sem_t			*sem_put_fd;
	pthread_t		thread;
}	t_philos;

t_philos	*init_philos(int argc, char **argv);
t_philos	*clear_all(t_philos *philos);
int			create_thread_for_process(t_philos *philos);
void		check_stop(t_philos *philos, int i);
size_t		diff_time(t_time now, t_time boot_time);
void		put_logs(t_man *man, enum e_strs mode);
void		philo_eat(t_man *man, t_philos *philos);
void		philo_sleep(t_man *man, t_philos *philos);
void		philo_think(t_man *man, t_philos *philos);
void		wait_exiting_thread(t_philos *philos);
void		set_end_flag(t_philos *philos, int flag);
int			get_end_flag(t_philos *philos);
void		increment_eat_cnt(t_man *man);
size_t		get_eat_cnt(t_man *man);
t_time		get_eat_time(t_man *man);
void		set_eat_time(t_man *man);
void		helper_sleep(int mtime);
size_t		get_neighbor_eat_cnt(t_man *man);
void		kill_process(t_philos *philos);
void		create_notice_process(t_philos *philos);
void		think_sleep(t_man *man, size_t sleep_time, t_philos *philos);

#endif
