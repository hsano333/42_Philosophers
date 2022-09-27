/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 20:41:26 by hsano             #+#    #+#             */
/*   Updated: 2022/09/27 15:30:59 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_death_flag(t_philos *philos, int flag)
{
	pthread_mutex_lock(&philos->mutex_check_death);
	philos->death_flag = flag;
	pthread_mutex_unlock(&philos->mutex_check_death);
}

int	get_death_flag(t_philos *philos)
{
	int	flag;

	pthread_mutex_lock(&philos->mutex_check_death);
	flag = philos->death_flag;
	pthread_mutex_unlock(&philos->mutex_check_death);
	return (flag);
}

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
			time_since_eat = diff_time(time, philos->boot_time);
			if (time_since_eat > (size_t)philos->time_die)
			{
				set_death_flag(philos, true);
				put_logs(&(philos->mans[i]), DIE);
				wait_exiting_thread(philos);
				return ;
			}
			usleep(100000);
			i++;
		}
	}
}
