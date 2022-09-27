/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:44:32 by hsano             #+#    #+#             */
/*   Updated: 2022/09/27 15:31:08 by hsano            ###   ########.fr       */
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
		if (get_death_flag(philos))
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
		if (pthread_create(&(philos->mans[i].thread), NULL, philo_loop, (void *)&(philos->mans[i])))
		{
			set_death_flag(philos, true);
			usleep(1000000);
			kill_oneself(philos);

		}
		i++;
	}
}
