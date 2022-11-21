/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:44:32 by hsano             #+#    #+#             */
/*   Updated: 2022/11/21 12:23:56 by hsano            ###   ########.fr       */
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
	if (!man->is_last && man->id % 2 == 1)
	{
		cnt = 0;
		while (cnt++ < (philos->time_eat) / 4)
		{
			if (get_neighbor_eat_cnt(man) == 0)
				usleep(10);
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

int	next_i(t_philos *philos, int i)
{
	if (i == philos->num - 1)
		return (1);
	else if (philos->num % 2 == 0)
	{
		if (i == philos->num - 2 - 1)
			return (0);
		i += 2;
		if (i >= philos->num)
			return (-1);
	}
	else
	{
		if (i == philos->num - 2)
			return (0);
		i += 2;
		if (i >= philos->num - 1)
			return (-1);
	}
	return (i);
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
		i = next_i(philos, i);
		if (i == -1)
			break ;
	}
	return (true);
}
