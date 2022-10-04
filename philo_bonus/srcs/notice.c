/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notice.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 00:52:52 by hsano             #+#    #+#             */
/*   Updated: 2022/10/04 18:56:45 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_notice_process(t_philos *philos)
{
	int	i;
	int	status;

	i = 0;
	philos->np_pid = fork();
	if (philos->np_pid < 0)
		kill_process(philos);
	else if (philos->np_pid == 0)
	{
		while (i < philos->num)
		{
			philos->mans[i].n_pid = fork();
			printf("fork i=%d, npid=%d", i, philos->mans[i].n_pid);
			if (philos->mans[i].n_pid < 0)
				kill_process(philos);
			else if (philos->mans[i].n_pid == 0)
			{
				while (1)
					usleep(500000000);
			}
			i++;
		}
		i = 0;
		while (i < philos->num)
		{
			printf("waitpid after No.0\n");
			waitpid(philos->mans[i].n_pid, &status, 0);
			printf("waitpid after No.1\n");
		}
	}
	else
	{
		//printf("notice parent No.1\n");
		//waitpid(philos->np_pid, &status, 0);
		//printf("notice parent No.2\n");
	}
}
