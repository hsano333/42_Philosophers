/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 21:32:05 by hsano             #+#    #+#             */
/*   Updated: 2022/11/30 14:25:29 by hsano            ###   ########.fr       */
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
	create_notice_process(philos);
	gettimeofday(&boot_time, NULL);
	philos->boot_time = boot_time;
	create_thread_for_process(philos);
	clear_all(philos);
	return (0);
}
