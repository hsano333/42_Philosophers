/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:44:32 by hsano             #+#    #+#             */
/*   Updated: 2022/09/28 13:05:47 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_loop(void *man_arg)
{
	t_man		*man;
	t_philos	*philos;

	man = (t_man *)man_arg;
	philos = (t_philos *)man->philos;
	if (man->id % 2 == 0)
		usleep(5000);
	while (1)
	{
		philo_eat(man);
		philo_sleep(man);
		philo_think(man);
		if (get_end_flag(philos))
			break ;
	}
	return (NULL);
}

int	create_thread(t_philos *philos)
{
	int	i;

	i = 0;
	while (i < philos->num)
	{
		if (pthread_create(&(philos->mans[i].thread), NULL, \
							philo_loop, (void *)&(philos->mans[i])))
		{
			set_end_flag(philos, true);
			printf("Error:stop simulation\n");
			return (false);
		}
		i++;
	}
	return (true);
}
