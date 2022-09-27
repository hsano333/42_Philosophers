/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 20:41:26 by hsano             #+#    #+#             */
/*   Updated: 2022/09/27 22:50:51 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_end_flag(t_philos *philos, int flag)
{
	pthread_mutex_lock(&philos->mutex_check_death);
	philos->end_flag = flag;
	pthread_mutex_unlock(&philos->mutex_check_death);
}

int	get_end_flag(t_philos *philos)
{
	int	flag;

	pthread_mutex_lock(&philos->mutex_check_death);
	flag = philos->end_flag;
	pthread_mutex_unlock(&philos->mutex_check_death);
	return (flag);
}

int	check_eat_cnt(t_philos *philos)
{
	int	i;

	if (philos->must_eat_num <= 0)
		return (false);
	i = 0;
	while (i < philos->num)
	{
		if (get_eat_cnt(&(philos->mans[i])) < (size_t)(philos->must_eat_num))
			return (false);
		i++;
	}
	return (true);
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
		if (check_eat_cnt(philos))
		{
			set_end_flag(philos, true);
			wait_exiting_thread(philos);
			return ;
		}
		while (i < philos->num)
		{

			gettimeofday(&time, NULL);
			time_since_eat = diff_time(time, philos->mans[i].timestamp_eating);
			//printf("time_since_eat=%zu\n", time_since_eat);
			if (time_since_eat > (size_t)philos->time_die * 1000 )
			{
				set_end_flag(philos, true);
				put_logs(&(philos->mans[i]), DIE);
				wait_exiting_thread(philos);
				return ;
			}
			usleep(500);
			i++;
		}
	}
}
