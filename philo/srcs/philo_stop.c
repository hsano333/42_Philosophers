/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_stop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 20:41:26 by hsano             #+#    #+#             */
/*   Updated: 2022/10/05 20:40:04 by hsano            ###   ########.fr       */
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
		if (get_eat_cnt(&(philos->mans[i])) \
				< (size_t)(philos->must_eat_num) * 2)
			return (false);
		i++;
	}
	return (true);
}

static int	check_death(t_philos *philos)
{
	int		i;
	t_time	time;
	size_t	time_since_eat;

	i = 0;
	while (i < philos->num)
	{
		gettimeofday(&time, NULL);
		time_since_eat = diff_time(time, philos->mans[i].timestamp_eating);
		if (time_since_eat / 1000 > (size_t)philos->time_die)
		{
			set_end_flag(philos, true);
			return (i + 1);
		}
		i++;
	}
	return (false);
}

void	check_stop(t_philos *philos)
{
	int	philo_no;

	while (1)
	{
		if (check_eat_cnt(philos))
		{
			set_end_flag(philos, true);
			break ;
		}
		philo_no = check_death(philos);
		if (philo_no > 0)
			break ;
		usleep(100);
	}
	put_logs(&(philos->mans[philo_no - 1]), DIE);
	wait_exiting_thread(philos);
}
