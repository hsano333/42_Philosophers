/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:13:31 by hsano             #+#    #+#             */
/*   Updated: 2022/11/21 13:09:32 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_eat_odd(t_man *man)
{
	t_philos	*philos;

	philos = (t_philos *)man->philos;
	if (get_end_flag(philos))
		return ;
	pthread_mutex_lock(man->mutex_right);
	put_logs(man, FORKS);
	pthread_mutex_lock(man->mutex_left);
	set_eat_time(man);
	put_logs(man, FORKS);
	increment_eat_cnt(man);
	put_logs(man, EAT);
	helper_sleep(philos->time_eat);
	increment_eat_cnt(man);
	pthread_mutex_unlock(man->mutex_left);
	pthread_mutex_unlock(man->mutex_right);
}

void	philo_eat_even(t_man *man)
{
	t_philos	*philos;

	philos = (t_philos *)man->philos;
	if (get_end_flag(philos))
		return ;
	pthread_mutex_lock(man->mutex_left);
	put_logs(man, FORKS);
	pthread_mutex_lock(man->mutex_right);
	set_eat_time(man);
	put_logs(man, FORKS);
	increment_eat_cnt(man);
	put_logs(man, EAT);
	helper_sleep(philos->time_eat);
	increment_eat_cnt(man);
	pthread_mutex_unlock(man->mutex_right);
	pthread_mutex_unlock(man->mutex_left);
}

void	philo_eat(t_man *man)
{
	t_philos	*philos;

	philos = (t_philos *)man->philos;
	if (get_end_flag(philos))
		return ;
	if (man->id % 2 == 1)
		philo_eat_odd(man);
	else
		philo_eat_even(man);
}

void	philo_sleep(t_man *man)
{
	t_philos	*philos;

	philos = (t_philos *)man->philos;
	if (get_end_flag(philos))
		return ;
	put_logs(man, SLEEP);
	helper_sleep(philos->time_slp);
}

void	philo_think(t_man *man)
{
	t_philos	*philos;
	int		cnt;

	philos = (t_philos *)man->philos;
	if (get_end_flag(philos))
		return ;
	put_logs(man, THINK);
	if (philos->num % 2 == 1)
	{
		cnt = 0;
		while (cnt < (philos->time_eat + philos->time_slp) / 4)
		{
			if (get_eat_cnt(man) > get_priority_eat_cnt(man))
				helper_usleep(100);
			else
				break ;
			cnt++;
		}
	}
}
