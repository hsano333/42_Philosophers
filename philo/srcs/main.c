/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 21:32:05 by hsano             #+#    #+#             */
/*   Updated: 2022/11/01 22:50:46 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philos	*philos;
	t_time		boot_time;

	philos = init_philos(argc, argv);
	if (!philos)
		return (1);
	gettimeofday(&boot_time, NULL);
	philos->boot_time = boot_time;
	//printf("create thread\n");
	if (create_thread(philos))
		check_stop(philos);
	clear_all(philos);
	return (0);
}
