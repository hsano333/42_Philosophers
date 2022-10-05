/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:00:42 by hsano             #+#    #+#             */
/*   Updated: 2022/10/05 22:18:18 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "stdlib.h"

t_philos	*clear_all(t_philos *philos)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&philos->mutex_print);
	pthread_mutex_destroy(&philos->mutex_check_death);
	while (i < philos->num)
	{
		pthread_mutex_destroy(&(philos->mans[i++].mutex_forks));
		pthread_mutex_destroy(&(philos->mans[i++].mutex_man));
	}
	free(philos->mans);
	free(philos);
	return (NULL);
}

size_t	diff_time(t_time now, t_time base)
{
	size_t	diff;

	if (now.tv_sec > base.tv_sec \
		|| (now.tv_sec - base.tv_sec == 0 && now.tv_usec >= base.tv_usec))
	{
		diff = (now.tv_sec - base.tv_sec) * 1000000 \
				+ (now.tv_usec - base.tv_usec);
	}
	else
		diff = 0;
	return (diff);
}

void	wait_exiting_thread(t_philos *philos)
{
	int	i;
	int	rval;

	i = 0;
	while (i < philos->num)
	{
		rval = pthread_join(philos->mans[i].thread, NULL);
		i++;
	}
}

void	helper_sleep(int mtime)
{
	t_time	begin;
	t_time	now;

	gettimeofday(&begin, NULL);
	while (1)
	{
		usleep(125);
		gettimeofday(&now, NULL);
		if ((diff_time(now, begin) / 1000) >= (size_t)mtime)
			break ;
	}
}
