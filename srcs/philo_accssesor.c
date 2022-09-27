/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_accssesor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 21:43:35 by hsano             #+#    #+#             */
/*   Updated: 2022/09/27 21:43:58 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	increment_eat_cnt(t_man *man)
{
	t_time	tmp_time;
	pthread_mutex_lock(&man->mutex_cnt_eat);
	man->cnt_eat++;
	gettimeofday(tmp_time, NULL);
	man->timestamp_eating = man->tmp_time;
	pthread_mutex_unlock(&man->mutex_cnt_eat);
}

size_t	get_eat_cnt(t_man *man)
{
	size_t	tmp;

	pthread_mutex_lock(&man->mutex_cnt_eat);
	tmp = man->cnt_eat;
	pthread_mutex_unlock(&man->mutex_cnt_eat);
	return (tmp);
}

