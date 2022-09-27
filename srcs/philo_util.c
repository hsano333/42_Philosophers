/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:00:42 by hsano             #+#    #+#             */
/*   Updated: 2022/09/27 15:30:20 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "stdlib.h"

void	clear_all(t_philos *philos)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&philos->mutex_print);
	pthread_mutex_destroy(&philos->mutex_check_death);
	while (i < philos->num)
		pthread_mutex_destroy(&(philos->mans[i++].mutex_forks));
	free(philos->mans);
	free(philos);
}

void	kill_oneself(t_philos *philos)
{
	clear_all(philos);
	exit(EXIT_FAILURE);
}

size_t	diff_time(t_time now, t_time boot_time)
{
	size_t	diff;
	
	diff = (now.tv_sec - boot_time.tv_sec) * 1000  + (now.tv_usec - boot_time.tv_usec) / 1000;
	return (diff);
}

void	wait_exiting_thread(t_philos *philos)
{
	int	i;

	i = 0;
	while (i < philos->num)
	{
		//pthread_detach(philos->mans[i].thread);
		pthread_join(philos->mans[i].thread, NULL);
		i++;
	}
}
