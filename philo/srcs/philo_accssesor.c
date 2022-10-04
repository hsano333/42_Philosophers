/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_accssesor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 21:43:35 by hsano             #+#    #+#             */
/*   Updated: 2022/10/05 02:29:02 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	increment_eat_cnt(t_man *man)
{
	pthread_mutex_lock(&man->mutex_man);
	man->cnt_eat++;
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

size_t	get_neighbor_eat_cnt(t_man *man)
{
	t_philos	*philos;
	int			prev;
	int			next;
	size_t		prev_eat_cnt;
	size_t		next_eat_cnt;

	philos = (t_philos *)man->philos;
	prev = man->id - 1 - 1;
	next = man->id - 1 + 1;
	if (man->id == 1)
		prev = philos->num - 1;
	else if (man->id == philos->num)
		next = 0;
	next_eat_cnt = get_eat_cnt(&(philos->mans[next]));
	if (diff_time(get_eat_time(man), get_eat_time(&(philos->mans[next]))) \
			> (size_t)philos->time_eat * 5 / 4)
		next_eat_cnt--;
	prev_eat_cnt = get_eat_cnt(&(philos->mans[prev]));
	if (diff_time(get_eat_time(man), get_eat_time(&(philos->mans[prev]))) \
			> (size_t)philos->time_eat * 5 / 4)
		prev_eat_cnt--;
	if (prev_eat_cnt >= next_eat_cnt)
		return (next_eat_cnt);
	return (prev_eat_cnt);
}
