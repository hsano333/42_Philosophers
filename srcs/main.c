/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 21:32:05 by hsano             #+#    #+#             */
/*   Updated: 2022/09/25 23:27:38 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <stdio.h>
int	main(int argc, char **argv)
{
	t_philo	*philo;

	philo = init_philo(argc, argv);
	if (!philo)
		return (1);
	printf("philo->no=%d\n", philo->philo_num);
	return (0);
}
