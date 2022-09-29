/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 16:12:27 by hsano             #+#    #+#             */
/*   Updated: 2022/09/29 16:01:30 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	set_default_value(t_philos *philos)
{
	t_time		boot_time;

	philos->end_flag = false;
	gettimeofday(&boot_time, NULL);
	philos->boot_time = boot_time;
	if (errno == EINVAL || errno == ENOMEM)
		return (false);
	if (errno == EINVAL || errno == ENOMEM)
		return (false);
	return (true);
}

t_philos	*init_philos_bonus(int argc, char **argv)
{
	int			i;
	t_philos	*philos;

	philos = parse_arg(argc, argv);
	if (!philos)
		return (NULL);
	if (!set_default_value(philos))
		pthread_mutex_init(&(philos->mutex_check_death), NULL);
	i = 0;
	if (i != philos->num)
		philos = clear_all(philos);
	return (philos);
}
