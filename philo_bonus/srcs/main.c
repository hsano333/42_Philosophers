/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 21:32:05 by hsano             #+#    #+#             */
/*   Updated: 2022/10/05 02:46:57 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philos	*philos;
	int			status;
	int			i;

	i = 0;
	philos = init_philos(argc, argv);
	if (!philos)
		return (1);
	create_notice_process(philos);
	if (philos->np_pid == 0)
	{
		create_thread_for_process(philos);
		while (i < philos->num)
		{
			waitpid(philos->mans[i].n_pid, &status, 0);
			i++;
		}
		clear_all(philos);
		exit(0);
	}
	else
		waitpid(philos->np_pid, &status, 0);
	return (0);
}
