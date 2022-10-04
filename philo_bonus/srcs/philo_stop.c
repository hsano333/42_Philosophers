/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_stop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 20:41:26 by hsano             #+#    #+#             */
/*   Updated: 2022/10/05 04:14:21 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_end_flag(t_philos *philos, int flag)
{
	philos->end_flag = flag;
}

int	get_end_flag(t_philos *philos)
{
	int	flag;

	flag = philos->end_flag;
	return (flag);
}

int	check_eat_cnt(t_philos *philos, int i)
{
	if (philos->must_eat_num <= 0)
		return (false);
	if (get_eat_cnt(&(philos->mans[i])) < (size_t)(philos->must_eat_num))
		return (false);
	return (true);
}

static int	check_death(t_philos *philos, int i)
{
	t_time	time;
	size_t	time_since_eat;

	gettimeofday(&time, NULL);
	time_since_eat = diff_time(time, philos->mans[i].timestamp_eating);
	if (time_since_eat / 1000 > (size_t)philos->time_die)
		return (true);
	return (false);
}

void	check_stop(t_philos *philos, int i)
{
	while (1)
	{
		if (check_eat_cnt(philos, i))
			kill(philos->mans[i].n_pid, 2);
		if (check_death(philos, i))
		{
			kill(philos->mans[i].n_pid, 2);
			put_logs(&(philos->mans[i]), DIE);
			break ;
		}
		usleep(1000);
	}
	pthread_detach(philos->mans[i].thread);
	kill_process(philos);
}
