/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notice.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 00:52:52 by hsano             #+#    #+#             */
/*   Updated: 2022/10/05 01:25:42 by hsano            ###   ########.fr       */
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
	{
		//printf("kill_process No.2\n");
		kill_process(philos);
	}
	else if (philos->np_pid == 0)
	{
		while (i < philos->num)
		{
			philos->mans[i].n_pid = fork();
			if (philos->mans[i].n_pid < 0)
			{
		//printf("kill_process No.3\n");
				kill_process(philos);
			}
			else if (philos->mans[i].n_pid == 0)
			{
				//printf("nfork i=%d, npid=%d\n", i, philos->mans[i].n_pid);
				while (1)
				{
					//philos->num++;
					usleep(1000000);
				}
				//printf("looploop\n");
				//printf("looploop\n");
				//printf("looploop\n");
			}
			else
			{
				//printf("npfork i=%d, npid=%d\n", i, philos->mans[i].n_pid);

			}
			i++;
		}
		i = 0;
		//printf("npfork end i=%d, npid=%d\n", i, philos->mans[i].n_pid);
		//printf("notic chichld\n");
		/*
		while (i < philos->num)
		{
			printf("waitpid after No.0\n");
			//waitpid(philos->mans[i].n_pid, &status, 0);
			printf("waitpid after No.1\n");
		}
		*/
	}
	else
	{
		//printf("notice parent No.1\n");
		waitpid(philos->np_pid, &status, 0);
		//printf("notice parent No.2\n");
	}
}
