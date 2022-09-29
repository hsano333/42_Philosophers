/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 16:12:27 by hsano             #+#    #+#             */
/*   Updated: 2022/09/28 16:13:31 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	while (i < philos->num)
	{
		pthread_mutex_init(&(philos->mans[i].mutex_forks), NULL);
		if (errno == EINVAL || errno == ENOMEM)
			break ;
		pthread_mutex_init(&(philos->mans[i].mutex_man), NULL);
		if (errno == EINVAL || errno == ENOMEM)
			break ;
		copy_mutex(philos, i);
		i++;
	}
	if (i != philos->num)
		philos = clear_all(philos);
	return (philos);
}
