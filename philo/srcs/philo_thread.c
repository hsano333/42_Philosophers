/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:44:32 by hsano             #+#    #+#             */
/*   Updated: 2022/10/05 23:05:30 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_loop(void *man_arg)
{
	t_man		*man;
	t_philos	*philos;
	int			cnt;

	man = (t_man *)man_arg;
	philos = (t_philos *)man->philos;


	if (man->id % 2 == 1 && man->id != philos->num)
	{
		cnt = 0;
		while (cnt < (philos->time_eat) / 2)
		{
			if (get_neighbor_eat_cnt(man) == 0)
				helper_sleep(1);
			else
				break ;
			cnt++;
		}
	}
	else
		usleep(100);


	/*
	if (man->id % 2 == 1 && man->id != philos->num)
	{
		while (get_neighbor_eat_cnt(man) == 0)
			usleep(50);
	}
	else
		usleep(100);
	*/
		//helper_sleep(philos->time_eat / 2);
		//if (get_neighbor_eat_cnt(man) == 0)
			//usleep(50);
			//}
		/*
		cnt = 0;
		while (cnt < (philos->time_eat + philos->time_slp) / 4)
		{
			if (get_neighbor_eat_cnt(man) == 0)
				helper_sleep(1);
			else
				break ;
			cnt++;
		}
		*/
	while (!get_end_flag(philos))
	{
		//printf("life No.1  man-id:%d\n", man->id);
		philo_eat(man);
		//printf("life No.2  man-id:%d\n", man->id);
		philo_sleep(man);
		//printf("life No.3  man-id:%d\n", man->id);
		philo_think(man);
		//printf("life No.4  man-id:%d\n", man->id);
	}
	//printf("life end man-id:%d\n", man->id);
	return (NULL);
}

int	create_thread(t_philos *philos)
{
	int	i;

	i = philos->num - 1;
	while (i < philos->num)
	{
		if (pthread_create(&(philos->mans[i].thread), NULL, \
							philo_loop, (void *)&(philos->mans[i])))
		{
			set_end_flag(philos, true);
			return (false);
		}
		if (philos->num == 1)
			break ;
		if (i == philos->num - 1)
		{
			usleep(300);
			i = 0;
		}
		else if (i == philos->num - 2)
			break ;
		else
			i++;
	}
	return (true);
}
