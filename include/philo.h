/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 22:59:19 by hsano             #+#    #+#             */
/*   Updated: 2022/09/28 00:12:10 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>

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
	size_t			cnt_eat;
	t_time			timestamp_eating;
	pthread_t		thread;
	pthread_mutex_t	mutex_man;
	pthread_mutex_t	mutex_forks;
	pthread_mutex_t	*mutex_left;
	pthread_mutex_t	*mutex_right;
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
	t_man			*mans;
	t_time			boot_time;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_check_death;
}	t_philos;

t_philos	*init_philos(int argc, char **argv);
void		clear_all(t_philos *philos);
void		kill_oneself(t_philos *philos);
void		create_thread(t_philos *philos);
void		check_stop(t_philos *philos);
size_t		diff_time(t_time now, t_time boot_time);
void		put_logs(t_man *man, enum e_strs mode);
void		philo_eat(t_man *man);
void		philo_sleep(t_man *man);
void		philo_think(t_man *man);
void		wait_exiting_thread(t_philos *philos);
void		set_end_flag(t_philos *philos, int flag);
int			get_end_flag(t_philos *philos);
void		increment_eat_cnt(t_man *man);
size_t		get_eat_cnt(t_man *man);
t_time		get_eat_time(t_man *man);
void		set_eat_time(t_man *man);

#endif
