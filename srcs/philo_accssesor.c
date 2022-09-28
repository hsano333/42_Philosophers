/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_accssesor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 21:43:35 by hsano             #+#    #+#             */
/*   Updated: 2022/09/28 12:35:30 by hsano            ###   ########.fr       */
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
