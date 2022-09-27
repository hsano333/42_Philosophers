/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:44:32 by hsano             #+#    #+#             */
/*   Updated: 2022/09/27 23:01:24 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_loop(void *man_arg)
{
	t_man	*man;
	t_philos	*philos;

	man = (t_man *)man_arg;
	philos = (t_philos *)man->philos;

	if (man->id % 2 == 0)
		usleep(2000);
	while (1)
	{
		philo_eat(man);
		philo_sleep(man);
		philo_think(man);
		if (get_end_flag(philos))
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
			set_end_flag(philos, true);
			kill_oneself(philos);
		}
		i++;
	}
}
