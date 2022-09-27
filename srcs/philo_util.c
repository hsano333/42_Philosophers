/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:00:42 by hsano             #+#    #+#             */
/*   Updated: 2022/09/27 13:08:30 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "stdlib.h"

void	clear_all(t_philos *philos)
{
	size_t	i;

	i = 0;
	free(philos->mans);
	free(philos);
}

void	kill_oneself(t_philos *philos)
{
	printf("kill oneself\n");
	clear_all(philos);
	exit(EXIT_FAILURE);
}

size_t	diff_time(t_time now, t_time boot_time)
{
	size_t	diff;
	//gettimeofday();
	//printf("boot_time:%ld:%d\n", boot_time.tv_sec, boot_time.tv_usec);
	//printf("now:%ld:%d\n", now.tv_sec, now.tv_usec);
	diff = (now.tv_sec - boot_time.tv_sec) * 1000  + (now.tv_usec - boot_time.tv_usec) / 1000;
	//printf("diff:%zu\n", diff);

	return (diff);
}

void	wait_exiting_thread(t_philos *philos)
{
	int	i;

	i = 0;
	while (i < philos->num)
	{
		pthread_detach(philos->mans[i].thread);

	}
}
