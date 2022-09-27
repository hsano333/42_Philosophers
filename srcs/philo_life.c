/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:13:31 by hsano             #+#    #+#             */
/*   Updated: 2022/09/27 23:55:25 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_eat_odd(t_man *man)
{
	t_philos	*philos;

	philos = (t_philos *)man->philos;
	if (get_end_flag(philos))
		return ;
	pthread_mutex_lock(man->mutex_left);
	put_logs(man, FORKS);
	pthread_mutex_lock(man->mutex_right);
	put_logs(man, FORKS);
	set_eat_time(man);
	put_logs(man, EAT);
	usleep(philos->time_eat * 1000);
	increment_eat_cnt(man);
	pthread_mutex_unlock(man->mutex_right);
	pthread_mutex_unlock(man->mutex_left);
}

static void	philo_eat_even(t_man *man)
{
	t_philos	*philos;

	philos = (t_philos *)man->philos;
	if (get_end_flag(philos))
		return ;
	pthread_mutex_lock(man->mutex_right);
	put_logs(man, FORKS);
	pthread_mutex_lock(man->mutex_left);
	put_logs(man, FORKS);
	set_eat_time(man);
	put_logs(man, EAT);
	usleep(philos->time_eat * 1000);
	increment_eat_cnt(man);
	pthread_mutex_unlock(man->mutex_left);
	pthread_mutex_unlock(man->mutex_right);
}

void	philo_eat(t_man *man)
{
	t_philos	*philos;

	philos = (t_philos *)man->philos;
	if (get_end_flag(philos))
		return ;
	if (man->id % 2 == 0)
		philo_eat_even(man);
	else
		philo_eat_odd(man);
}

void	philo_sleep(t_man *man)
{
	t_philos	*philos;

	philos = (t_philos *)man->philos;
	if (get_end_flag(philos))
		return ;
	put_logs(man, SLEEP);
	usleep(philos->time_slp * 1000);
}

void	philo_think(t_man *man)
{
	t_philos	*philos;

	philos = (t_philos *)man->philos;
	if (get_end_flag(philos))
		return ;
	put_logs(man, THINK);
}
