/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:44:32 by hsano             #+#    #+#             */
/*   Updated: 2022/10/05 23:11:39 by hsano            ###   ########.fr       */
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
		while (cnt++ < (philos->time_eat) / 2)
		{
			if (get_neighbor_eat_cnt(man) == 0)
				helper_sleep(1);
			else
				break ;
		}
	}
	while (!get_end_flag(philos))
	{
		philo_eat(man);
		philo_sleep(man);
		philo_think(man);
	}
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
