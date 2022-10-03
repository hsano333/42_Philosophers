/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notice.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 00:52:52 by hsano             #+#    #+#             */
/*   Updated: 2022/10/04 01:15:32 by hsano            ###   ########.fr       */
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
			if (philos->mans[i].n_pid < 0)
				kill_process(philos);
			else if (philos->mans[i].n_pid == 0)
			{
				while (1)
					usleep(100000);
			}
			//else{
			//}
			i++;
		}
		i = 0;
		printf("notice child end waitpid No.0\n");
		while (i < philos->num)
		{
			waitpid(philos->mans[i].n_pid, &status, 0);
		}
	}
	else
	{
		printf("notice waitpid No.1\n");
		//waitpid(philos->np_pid, &status, 0);
		printf("notice waitpid No.2\n");

	}
	printf("notice waitpid No.3\n");
}
