/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_flag_accssesor.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 20:31:41 by hsano             #+#    #+#             */
/*   Updated: 2022/11/01 20:41:17 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_end_flag(t_philos *philos, int flag)
{
	pthread_mutex_lock(&philos->mutex_check_death);
	philos->end_flag = flag;
	pthread_mutex_unlock(&philos->mutex_check_death);
}

int	get_end_flag(t_philos *philos)
{
	int	flag;

	pthread_mutex_lock(&philos->mutex_check_death);
	flag = philos->end_flag;
	pthread_mutex_unlock(&philos->mutex_check_death);
	return (flag);
}


void	set_start_flag(t_philos *philos, int flag)
{
	pthread_mutex_lock(&philos->mutex_check_death);
	philos->start_flag = flag;
	pthread_mutex_unlock(&philos->mutex_check_death);
}

int	get_start_flag(t_philos *philos)
{
	int	flag;

	pthread_mutex_lock(&philos->mutex_check_death);
	flag = philos->start_flag;
	pthread_mutex_unlock(&philos->mutex_check_death);
	return (flag);
}

