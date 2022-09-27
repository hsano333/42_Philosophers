/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:44:32 by hsano             #+#    #+#             */
/*   Updated: 2022/09/27 12:57:42 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_loop(void *man_arg)
{
	t_man	*man;
	t_philos	*philos;

	man = (t_man *)man_arg;
	philos = (t_philos *)man->philos;

	//if (man->id % 2 == 1)
		//usleep(200);
	while (1)
	{
		if (man->id % 2 == 0)
			philo_eat_even(man);
		else 
			philo_eat_odd(man);
		philo_sleep(man);
		philo_think(man);
		if (philos->death_flag)
			break ;
	}
	pthread_exit(0);
}

void	create_thread(t_philos *philos)
{
	int	i;

	i = 0;
	while (i < philos->num)
	{
		printf("i=%d\n", i);
		pthread_create(&(philos->mans[i].thread), NULL, philo_loop, (void *)&(philos->mans[i]));
		i++;
	}
	printf("after create\n");
}
