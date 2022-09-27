/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 23:03:57 by hsano             #+#    #+#             */
/*   Updated: 2022/09/27 16:16:22 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_atoi.h"
#include "philo.h"
#include "sys/errno.h"
# include <pthread.h>

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

static	t_philos *parse_arg(int argc, char **argv)
{
	t_philos	*philos;
	int		error[5];

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
	if (has_error(error, argc) || !philos->mans || philos->num < 0 \
			|| philos->time_die < 0 || philos->time_eat < 0 \
			|| philos->time_slp < 0 || philos->must_eat_num < 0)
	{
		free(philos->mans);
		free(philos);
		return (NULL);
	}
	return (philos);
}

static void	copy_mutex(t_philos *philos, int i)
{

	philos->mans[i].id = i + 1;
	philos->mans[i].philos = (void *)philos;
	philos->mans[i].mutex_right = &(philos->mans[i].mutex_forks);
	if (i > 0)
		philos->mans[i].mutex_left = &(philos->mans[i - 1].mutex_forks);
	if (i == philos->num - 1)
	{
		philos->mans[0].mutex_left = &(philos->mans[i].mutex_forks);
	}
	//philos->info = 
	//philos->mans[i].time_die = philos->time_die;
	//philos->mans[i].time_eat = philos->time_eat;
	//philos->mans[i].time_slp = philos->time_slp;
	//philos->mans[i].boot_time = philos->boot_time;
}

static int	set_default_value(t_philos *philos)
{
	t_time		boot_time;

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
			kill_oneself(philos);
		pthread_mutex_init(&(philos->mans[i].mutex_cnt_eat), NULL);
		if (errno == EINVAL || errno == ENOMEM)
			kill_oneself(philos);
		copy_mutex(philos, i);
		i++;
	}
	return (philos);
}