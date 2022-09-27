/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_logs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:16:21 by hsano             #+#    #+#             */
/*   Updated: 2022/09/27 12:56:37 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	put_logs_selected(t_man *man, enum e_strs mode)
{
	t_time		now;
	size_t		diff;
	t_philos	*philos;

	philos = (t_philos *)man->philos;
	gettimeofday(&now, NULL);
	diff = diff_time(now, philos->boot_time);
	if (mode == FORKS)
		printf(" %.8zu %d has taken a fork\n", diff, man->id);
	else if (mode == EAT)
		printf(" %.8zu %d is eating\n", diff, man->id);
	else if (mode == SLEEP)
		printf(" %.8zu %d is sleeping\n", diff, man->id);
	else if (mode == THINK)
		printf(" %.8zu %d is thinking\n", diff, man->id);
	else if (mode == DIE)
		printf(" %.8zu %d died\n", diff, man->id);
}

void	put_logs(t_man *man, enum e_strs mode)
{
	t_philos	*philos;

	philos = (t_philos *)man->philos;
	pthread_mutex_lock(&philos->mutex_print);


	if (philos->death_flag && mode == DIE)
		put_logs_selected(man, mode);
	else if (!philos->death_flag)
		put_logs_selected(man, mode);
	pthread_mutex_unlock(&philos->mutex_print);
}
