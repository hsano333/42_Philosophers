/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:50:16 by hsano             #+#    #+#             */
/*   Updated: 2022/09/27 23:36:35 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	increment_eat_cnt(t_man *man)
{
	//t_time	tmp_time;

	pthread_mutex_lock(&man->mutex_man);
	man->cnt_eat++;
	//gettimeofday(&tmp_time, NULL);
	//man->timestamp_eating = man->tmp_time;
	pthread_mutex_unlock(&man->mutex_man);
}

size_t	get_eat_cnt(t_man *man)
{
	size_t	tmp;

	pthread_mutex_lock(&man->mutex_man);
	tmp = man->cnt_eat;
	pthread_mutex_unlock(&man->mutex_man);
	return (tmp);
}

void	set_eat_time(t_man *man)
{
	t_time	time;

	pthread_mutex_lock(&man->mutex_man);
	gettimeofday(&time, NULL);
	man->timestamp_eating = time;
	//man->timestamp_eating.tv_sec = time.tv_sec;
	//man->timestamp_eating.tv_usec = time.tv_usec;
	pthread_mutex_unlock(&man->mutex_man);
}

t_time	get_eat_time(t_man *man)
{
	t_time	tmp;

	pthread_mutex_lock(&man->mutex_man);
	tmp = man->timestamp_eating;
	pthread_mutex_unlock(&man->mutex_man);
	return (tmp);
}

void	philo_eat_odd(t_man *man)
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
	//gettimeofday(&man->timestamp_eating, NULL);
	put_logs(man, EAT);
	usleep(philos->time_eat * 1000);
	increment_eat_cnt(man);
	pthread_mutex_unlock(man->mutex_right);
	pthread_mutex_unlock(man->mutex_left);
}

void	philo_eat_even(t_man *man)
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
	//gettimeofday(&man->timestamp_eating, NULL);
	put_logs(man, EAT);
	usleep(philos->time_eat * 1000);
	increment_eat_cnt(man);
	pthread_mutex_unlock(man->mutex_left);
	pthread_mutex_unlock(man->mutex_right);
}

