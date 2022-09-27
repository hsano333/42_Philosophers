/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:13:31 by hsano             #+#    #+#             */
/*   Updated: 2022/09/27 10:58:34 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat_odd(t_man *man)
{
	t_philos	*philos;

	philos = (t_philos *)man->philos;
	pthread_mutex_lock(man->mutex_left);
	put_logs(man, FORKS);
	pthread_mutex_lock(man->mutex_right);
	put_logs(man, FORKS);
	gettimeofday(&man->timestamp_eating, NULL);
	put_logs(man, EAT);
	usleep(philos->time_eat);
	pthread_mutex_unlock(man->mutex_right);
	pthread_mutex_unlock(man->mutex_left);
}

void	philo_eat_even(t_man *man)
{
	t_philos	*philos;

	philos = (t_philos *)man->philos;
	pthread_mutex_lock(man->mutex_right);
	put_logs(man, FORKS);
	pthread_mutex_lock(man->mutex_left);
	put_logs(man, FORKS);
	gettimeofday(&man->timestamp_eating, NULL);
	put_logs(man, EAT);
	usleep(philos->time_eat);
	pthread_mutex_unlock(man->mutex_left);
	pthread_mutex_unlock(man->mutex_right);
}

void	philo_sleep(t_man *man)
{
	t_philos	*philos;

	philos = (t_philos *)man->philos;
	put_logs(man, SLEEP);
	usleep(philos->time_slp);
}

void	philo_think(t_man *man)
{
	put_logs(man, THINK);
}

