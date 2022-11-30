/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_logs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:16:21 by hsano             #+#    #+#             */
/*   Updated: 2022/11/30 13:56:56 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#define TIME_WIDTH 19

static void	write_message(t_philos *philos, size_t diff, int id, char *str)
{
	char	out[256];
	char	tmp[256];
	int		i;
	int		k;

	if (!ft_itoa_no_memory(diff, TIME_WIDTH + 1, tmp, out))
		set_end_flag(philos, true);
	out[TIME_WIDTH + 1] = ' ';
	i = TIME_WIDTH + 2;
	i += ft_itoa_no_memory(id, 0, tmp, &(out[i]));
	k = -1;
	out[i] = ' ';
	while (str[++k])
		out[++i] = str[k];
	write(1, out, i + 1);
}

static void	put_logs_selected(t_man *man, enum e_strs mode)
{
	t_time		now;
	size_t		diff;
	t_philos	*philos;

	philos = (t_philos *)man->philos;
	gettimeofday(&now, NULL);
	diff = diff_time(now, philos->boot_time) / 1000;
	if (mode == FORKS)
		write_message(philos, diff, man->id, "has taken a fork\n");
	else if (mode == EAT)
		write_message(philos, diff, man->id, "is eating\n");
	else if (mode == SLEEP)
		write_message(philos, diff, man->id, "is sleeping\n");
	else if (mode == THINK)
		write_message(philos, diff, man->id, "is thinking\n");
	else if (mode == DIE)
		write_message(philos, diff, man->id, "died\n");
}

void	put_logs(t_man *man, enum e_strs mode)
{
	t_philos	*philos;

	philos = (t_philos *)man->philos;
	pthread_mutex_lock(&philos->mutex_print);
	if (mode == DIE)
		put_logs_selected(man, mode);
	else if (!get_end_flag(philos))
		put_logs_selected(man, mode);
	pthread_mutex_unlock(&philos->mutex_print);
}
