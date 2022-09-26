/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 23:03:57 by hsano             #+#    #+#             */
/*   Updated: 2022/09/25 23:32:08 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_atoi.h"
#include "philo.h"

static int	has_error(int *error)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (error[i++] == true)
			return (true);
	}
	return (false);
}

t_philo	*init_philo(int argc, char **argv)
{
	t_philo	*philo;
	int		error[5];

	if (!(5 <= argc && argc <= 6))
		return (NULL);
	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->philo_num = ft_atoi(argv[1], &(error[0]));
	philo->time_die = ft_atoi(argv[2], &(error[1]));
	philo->time_eat = ft_atoi(argv[3], &(error[2]));
	philo->time_slp = ft_atoi(argv[4], &(error[3]));
	philo->must_eat_num = 0;
	if (argc == 6)
		philo->must_eat_num = ft_atoi(argv[5], &(error[4]));
	if (has_error(error))
	{
		free(philo);
		return (NULL);
	}
	return (philo);
}
