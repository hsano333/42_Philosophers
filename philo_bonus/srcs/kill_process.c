/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 19:08:58 by hsano             #+#    #+#             */
/*   Updated: 2022/10/06 01:46:08 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	kill_all(t_philos *philos)
{
	int	i;

	i = 0;
	while (i < philos->num)
	{
		kill(philos->mans[i].pid, 2);
		kill(philos->mans[i].n_pid, 2);
		i++;
	}
}

void	kill_process(t_philos *philos)
{
	kill_all(philos);
	clear_all(philos);
	sem_close(philos->sem_fd);
	sem_unlink(philos->sem_name);
	sem_close(philos->sem_put_fd);
	sem_unlink(philos->sem_put_name);
	kill(0, 2);
	exit(EXIT_FAILURE);
}
