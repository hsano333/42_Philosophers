/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_neighbor_eat_cnt.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:47:51 by hsano             #+#    #+#             */
/*   Updated: 2022/11/21 14:15:11 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_neighbor_eat_cnt(t_man *man)
{
	t_philos	*philos;
	int			prev;
	int			next;
	size_t		prev_eat_cnt;
	size_t		next_eat_cnt;

	philos = (t_philos *)man->philos;
	prev = man->id - 1 - 1;
	next = man->id - 1 + 1;
	if (man->id == 1)
		prev = philos->num - 1;
	else if (man->id == philos->num)
		next = 0;
	next_eat_cnt = get_eat_cnt(&(philos->mans[next]));
	if (diff_time(get_eat_time(man), get_eat_time(&(philos->mans[next]))) \
			> (size_t)philos->time_eat * 5 / 4)
		next_eat_cnt--;
	prev_eat_cnt = get_eat_cnt(&(philos->mans[prev]));
	if (diff_time(get_eat_time(man), get_eat_time(&(philos->mans[prev]))) \
			> (size_t)philos->time_eat * 5 / 4)
		prev_eat_cnt--;
	if (prev_eat_cnt >= next_eat_cnt)
		return (next_eat_cnt);
	return (prev_eat_cnt);
}

size_t	get_priority_eat_cnt(t_man *man)
{
	t_philos	*philos;

	philos = (t_philos *)man->philos;
	if (man->is_last)
		return (INT_MAX);
	else if (man->id == 1)
		return (get_eat_cnt(&(philos->mans[philos->num - 1])));
	else
		return (get_eat_cnt(&(philos->mans[man->id - 2 - 1])));
}
