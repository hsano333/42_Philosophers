/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 20:41:26 by hsano             #+#    #+#             */
/*   Updated: 2022/09/27 13:01:56 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_death(t_philos *philos)
{
	int		i;
	t_time	time;
	size_t	time_since_eat;
	
	i = 0;
	while (1)
	{
		i = 0;
		while (i < philos->num)
		{

			gettimeofday(&time, NULL);
			//tv_usec
			//tv_usec
			//printf("No.1 check death test i=%ld, %u\n", time.tv_sec,  time.tv_usec);
			//printf("No.2 check death test i=%u\n", time.tv_usec - philos->boot_time.tv_usec);
			time_since_eat = diff_time(time, philos->boot_time);
			if (time_since_eat > philos->time_die)
			{
				philos->death_flag = true;
				put_logs(&(philos->mans[i]), DIE);
				wait_exiting_thread(philos);
				//pthread_mutex_lock(&philos->mutex_print);
				//kill_threads();

				//pthread_mutex_lock(&philos->mutex_print);
			}
			//printf("i=%d,time_since_eat=%zu\n",i, time_since_eat);
			usleep(100);
			i++;
		}
	}
}
