/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 19:08:58 by hsano             #+#    #+#             */
/*   Updated: 2022/10/04 21:12:32 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	kill_all(t_philos *philos)
{
	int	i;

	i = 0;
	printf("kill_all No.1 \n");
	while (i < philos->num)
	{
		kill(philos->mans[i].pid, 2);
		kill(philos->mans[i].n_pid, 2);
		i++;
	}
}

void	kill_process(t_philos *philos)
{
	printf("kill_all No.2 \n");
	kill_all(philos);
	clear_all(philos);
	sem_close(philos->sem_fd);
	sem_unlink(philos->sem_name);
	exit(EXIT_FAILURE);
}
