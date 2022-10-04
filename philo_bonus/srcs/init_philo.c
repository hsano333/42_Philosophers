/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 23:03:57 by hsano             #+#    #+#             */
/*   Updated: 2022/10/05 02:36:50 by hsano            ###   ########.fr       */
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

static t_philos	*parse_arg(int argc, char **argv)
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

static void	copy_man(t_philos *philos, int i)
{
	philos->mans[i].id = i + 1;
	philos->mans[i].philos = (void *)philos;
	philos->mans[i].timestamp_eating = philos->boot_time;
}

static int	set_default_value(t_philos *philos)
{
	t_time		boot_time;

	philos->end_flag = false;
	gettimeofday(&boot_time, NULL);
	philos->boot_time = boot_time;
	philos->sem_name = "fork11";
	philos->sem_fd = sem_open(philos->sem_name, O_CREAT, 0777, philos->num);
	sem_close(philos->sem_fd);
	sem_unlink(philos->sem_name);
	philos->sem_fd = sem_open(philos->sem_name, O_CREAT, 0777, philos->num);
	if (philos->sem_fd == SEM_FAILED)
	{
		kill_process(philos);
		return (false);
	}
	return (true);
}

t_philos	*init_philos(int argc, char **argv)
{
	int			i;
	t_philos	*philos;

	philos = parse_arg(argc, argv);
	if (!philos)
		return (NULL);
	set_default_value(philos);
	i = 0;
	while (i < philos->num)
	{
		copy_man(philos, i);
		i++;
	}
	return (philos);
}
