/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notice.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 00:52:52 by hsano             #+#    #+#             */
/*   Updated: 2022/10/03 14:35:24 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_notice_process(t_philos *philos)
{
	int	i;

	i = 0;
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
		i++;
	}
}

