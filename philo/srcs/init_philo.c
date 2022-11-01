/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 23:03:57 by hsano             #+#    #+#             */
/*   Updated: 2022/11/01 23:08:45 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_atoi.h"
#include "philo.h"
#include "sys/errno.h"
#include <pthread.h>

static int	has_error(int *error, int argc)
{
	int	i;

	i = 0;
	while (i < argc - 1)
	{
		if (error[i++] == true)
		{
			return (true);
		}
	}
	return (false);
}

t_philos	*parse_arg(int argc, char **argv)
{
	t_philos	*philos;
	int			error[5];

	if (!(5 <= argc && argc <= 6))
		return (NULL);
	philos = (t_philos *)malloc(sizeof(t_philos));
	if (!philos)
		return (NULL);
	philos->num = ft_atoi(argv[1], &(error[0]));
	philos->time_die = ft_atoi(argv[2], &(error[1]));
	philos->time_eat = ft_atoi(argv[3], &(error[2]));
	philos->time_slp = ft_atoi(argv[4], &(error[3]));
	philos->must_eat_num = 0;
	if (argc == 6)
		philos->must_eat_num = ft_atoi(argv[5], &(error[4]));
	philos->mans = (t_man *)malloc(sizeof(t_man) * philos->num);
	if (has_error(error, argc) || !philos->mans || philos->num <= 0 \
			|| philos->time_die < 0 || philos->time_eat < 0 \
			|| philos->time_slp < 0 || philos->must_eat_num < 0)
	{
		free(philos->mans);
		free(philos);
		return (NULL);
	}
	return (philos);
}

static void	copy_man(t_philos *philos, int i)
{
	philos->mans[i].id = i + 1;
	philos->mans[i].is_last = false;
	if (i == philos->num - 1)
		philos->mans[i].is_last = true;
	philos->mans[i].philos = (void *)philos;
	philos->mans[i].mutex_right = &(philos->mans[i].mutex_forks);
	//set_eat_time(&(philos->mans[i]), &(philos->boot_time));
	philos->mans[i].timestamp_eating = philos->boot_time;
	if (i > 0)
		philos->mans[i].mutex_left = &(philos->mans[i - 1].mutex_forks);
	if (i == philos->num - 1)
		philos->mans[0].mutex_left = &(philos->mans[i].mutex_forks);
}

static int	set_default_value(t_philos *philos)
{
	t_time		boot_time;

	philos->start_flag = false;
	philos->end_flag = false;
	gettimeofday(&boot_time, NULL);
	philos->boot_time = boot_time;
	pthread_mutex_init(&(philos->mutex_print), NULL);
	if (errno == EINVAL || errno == ENOMEM)
		return (false);
	pthread_mutex_init(&(philos->mutex_check_death), NULL);
	if (errno == EINVAL || errno == ENOMEM)
		return (false);
	return (true);
}

t_philos	*init_philos(int argc, char **argv)
{
	int			i;
	t_philos	*philos;

	philos = parse_arg(argc, argv);
	if (!philos)
		return (NULL);
	if (!set_default_value(philos))
		pthread_mutex_init(&(philos->mutex_check_death), NULL);
	i = 0;
	while (i < philos->num)
	{
		pthread_mutex_init(&(philos->mans[i].mutex_forks), NULL);
		if (errno == EINVAL || errno == ENOMEM)
			break ;
		pthread_mutex_init(&(philos->mans[i].mutex_man), NULL);
		if (errno == EINVAL || errno == ENOMEM)
			break ;
		copy_man(philos, i);
		i++;
	}
	if (i != philos->num)
		philos = clear_all(philos);
	return (philos);
}
