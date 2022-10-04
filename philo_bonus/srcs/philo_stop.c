/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_stop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 20:41:26 by hsano             #+#    #+#             */
/*   Updated: 2022/10/05 00:23:37 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_end_flag(t_philos *philos, int flag)
{
	//pthread_mutex_lock(&philos->mutex_check_death);
	philos->end_flag = flag;
	//printf("set flag:%d\n", flag);
	//pthread_mutex_unlock(&philos->mutex_check_death);
}

int	get_end_flag(t_philos *philos)
{
	int	flag;

	//pthread_mutex_lock(&philos->mutex_check_death);
	//printf("No.1 get flag=%p\n", philos);
	flag = philos->end_flag;
	//printf("No.2 get flag=%d\n", flag);
	//pthread_mutex_unlock(&philos->mutex_check_death);
	return (flag);
}

int	check_eat_cnt(t_philos *philos, int i)
{
	//int	i;

	if (philos->must_eat_num <= 0)
		return (false);
	//i = 0;
	//while (i < philos->num)
	//{
	if (get_eat_cnt(&(philos->mans[i])) < (size_t)(philos->must_eat_num))
		return (false);
		//i++;
	//}
	return (true);
}

static int	check_death(t_philos *philos, int i)
{
	t_time	time;
	size_t	time_since_eat;

	//while (i < philos->num)
	{
		gettimeofday(&time, NULL);
		time_since_eat = diff_time(time, philos->mans[i].timestamp_eating);
		if (time_since_eat > (size_t)philos->time_die * 1000)
		{
			//put_logs(&(philos->mans[i]), DIE);
			//wait_exiting_thread(philos);
			return (true);
		}
		//i++;
	}
	return (false);
}

void	check_stop(t_philos *philos, int i)
{
	while (1)
	{
		if (check_eat_cnt(philos, i))
		{
			printf("kill check eat death No.1 i=%d, n_pid=%d\n", i, philos->mans[i].n_pid);
			kill(philos->mans[i].n_pid, 3);
			//set_end_flag(philos, true);
			//wait_exiting_thread(philos);
			break ;
		}
		if (check_death(philos, i))
		{
			printf("kill check death No.2 philos->np_pid:%d, philos->pp_pid:%d\n", philos->np_pid, philos->pp_pid);
			kill(philos->np_pid, 2);
			put_logs(&(philos->mans[i]), DIE);
			kill(philos->pp_pid, 2);
			clear_all(philos);
			exit(0);
		}
		usleep(2000);
	}
	printf("kill check death No.3 philos->np_pid:%d, philos->pp_pid:%d\n", philos->np_pid, philos->pp_pid);
}
