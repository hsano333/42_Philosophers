/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_logs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:16:21 by hsano             #+#    #+#             */
/*   Updated: 2022/10/05 01:58:32 by hsano            ###   ########.fr       */
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
	diff = diff_time(now, philos->boot_time) / 1000;
	if (mode == FORKS)
		printf("%.10zu %d has taken a fork\n", diff, man->id);
	else if (mode == EAT)
		printf("%.10zu %d is eating\n", diff, man->id);
	else if (mode == SLEEP)
		printf("%.10zu %d is sleeping\n", diff, man->id);
	else if (mode == THINK)
		printf("%.10zu %d is thinking\n", diff, man->id);
	else if (mode == DIE)
		printf("%.10zu %d died\n", diff, man->id);
}

void	put_logs(t_man *man, enum e_strs mode)
{
	t_philos	*philos;

	philos = (t_philos *)man->philos;
	pthread_mutex_lock(&philos->mutex_print);
	//if (get_end_flag(philos) && mode == DIE)
	if (mode == DIE)
		put_logs_selected(man, mode);
	else if (!get_end_flag(philos))
		put_logs_selected(man, mode);
	pthread_mutex_unlock(&philos->mutex_print);
}
