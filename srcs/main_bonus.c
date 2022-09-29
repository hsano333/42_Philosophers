/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 11:40:46 by hsano             #+#    #+#             */
/*   Updated: 2022/09/28 16:13:27 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_philos	*philos;

	philos = init_philos_bonus(argc, argv);
	if (!philos)
		return (1);
	if (create_thread(philos))
		check_stop(philos);
	clear_all(philos);
	return (0);
}
