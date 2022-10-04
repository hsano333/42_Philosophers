/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:13:31 by hsano             #+#    #+#             */
/*   Updated: 2022/10/05 02:33:56 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat_even(t_man *man)
{
	t_philos	*philos;

	philos = (t_philos *)man->philos;
	if (get_end_flag(philos))
		return ;
}

void	philo_eat(t_man *man, t_philos *philos)
{
	if (get_end_flag(philos))
		return ;
	sem_wait(philos->sem_fd);
	put_logs(man, FORKS);
	sem_wait(philos->sem_fd);
	put_logs(man, FORKS);
	set_eat_time(man);
	put_logs(man, EAT);
	helper_sleep(philos->time_eat);
	increment_eat_cnt(man);
	sem_post(philos->sem_fd);
	sem_post(philos->sem_fd);
}

void	philo_sleep(t_man *man, t_philos *philos)
{
	if (get_end_flag(philos))
		return ;
	put_logs(man, SLEEP);
	helper_sleep(philos->time_slp);
}

void	think_sleep(t_man *man, size_t sleep_time, t_philos *philos)
{
	if ((philos->num % 2 == 0) && ((int)(man->cnt_eat % 2) == (man->id % 2)))
	{
		if (man->cnt_eat == 0)
			helper_sleep(sleep_time);
	}
	else if (philos->num % 2 == 1)
	{
		if (((int)(man->cnt_eat % 3) == (man->id % 3)))
			helper_sleep(sleep_time);
	}
}

void	philo_think(t_man *man, t_philos *philos)
{
	t_time	time;
	size_t	time_since_eat;
	size_t	wait_time;

	gettimeofday(&time, NULL);
	time_since_eat = diff_time(time, man->timestamp_eating);
	wait_time = (size_t)((philos->time_eat + philos->time_slp) / 10);
	put_logs(man, THINK);
	if (time_since_eat > wait_time)
		think_sleep(man, wait_time, philos);
	if (get_end_flag(philos))
		return ;
}
