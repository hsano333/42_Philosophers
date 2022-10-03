/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:00:42 by hsano             #+#    #+#             */
/*   Updated: 2022/10/04 02:00:51 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "stdlib.h"

t_philos	*clear_all(t_philos *philos)
{
	//int	i;

	//i = 0;
	//pthread_mutex_destroy(&philos->mutex_print);
	//pthread_mutex_destroy(&philos->mutex_check_death);
	//while (i < philos->num)
		//pthread_mutex_destroy(&(philos->mans[i++].mutex_forks));
	sem_close(philos->sem_fd);
	sem_unlink(philos->sem_name);
	free(philos->mans);
	free(philos);
	return (NULL);
}

size_t	diff_time(t_time now, t_time base_time)
{
	size_t	diff;

	if (now.tv_sec > base_time.tv_sec \
			|| (now.tv_sec - base_time.tv_sec == 0 && now.tv_usec >= base_time.tv_usec))
	{
		diff = (now.tv_sec - base_time.tv_sec) * 1000000 \
				+ (now.tv_usec - base_time.tv_usec);
	}
	else
		diff = 0;
	return (diff);
}

void	wait_exiting_thread(t_philos *philos)
{
	int	i;

	i = 0;
	while (i < philos->num)
	{
		pthread_detach(philos->mans[i].thread);
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
		usleep(100);
		gettimeofday(&now, NULL);
		if ((diff_time(now, begin) / 1000) >= (size_t)mtime)
			break ;
	}
}
