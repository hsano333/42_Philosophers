/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:13:31 by hsano             #+#    #+#             */
/*   Updated: 2022/09/27 16:16:38 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_man *man)
{
	t_philos	*philos;

	philos = (t_philos *)man->philos;
	if (get_end_flag(philos))
		return ;
	if (man->id % 2 == 0)
		philo_eat_even(man);
	else 
		philo_eat_odd(man);
}

void	philo_sleep(t_man *man)
{
	t_philos	*philos;

	philos = (t_philos *)man->philos;
	if (get_end_flag(philos))
		return ;
	put_logs(man, SLEEP);
	usleep(philos->time_slp * 1000);
}

void	philo_think(t_man *man)
{
	t_philos	*philos;

	philos = (t_philos *)man->philos;
	if (get_end_flag(philos))
		return ;
	put_logs(man, THINK);
}

