/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:44:32 by hsano             #+#    #+#             */
/*   Updated: 2022/10/05 02:58:45 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_loop(void *man_arg)
{
	t_man		*man;
	t_philos	*philos;

	man = (t_man *)man_arg;
	philos = (t_philos *)man->philos;
	think_sleep(man, (philos->time_eat + philos->time_slp) / 4, philos);
	while (1)
	{
		philo_eat(man, philos);
		philo_sleep(man, philos);
		philo_think(man, philos);
		if (get_end_flag(philos))
			exit(1);
	}
	exit(0);
	return (NULL);
}

void	wait_child(t_philos *philos)
{
	int		i;
	int		status;

	i = 0;
	while (i < philos->num)
	{
		waitpid(philos->mans[i].n_pid, &status, 0);
		i++;
	}
}

void	*man_process(void	*arg)
{
	t_man		*man;
	t_philos	*philos;

	man = (t_man *)arg;
	philos = man->philos;
	if (pthread_create(&man->thread, NULL, philo_loop, man))
		kill_process(philos);
	check_stop(philos, man->id - 1);
	return (NULL);
}

void	process_child(t_philos *philos)
{
	int		i;

	i = 0;
	while (i < philos->num)
	{
		philos->mans[i].pid = fork();
		if (philos->mans[i].pid < 0)
			kill_process(philos);
		else if (philos->mans[i].pid == 0)
		{
			man_process(&(philos->mans[i]));
			exit(0);
		}
		i++;
	}
}

int	create_thread_for_process(t_philos *philos)
{
	t_time	boot_time;

	philos->pp_pid = fork();
	if (philos->pp_pid < 0)
		kill_process(philos);
	else if (philos->pp_pid == 0)
	{
		gettimeofday(&boot_time, NULL);
		philos->boot_time = boot_time;
		process_child();
		wait_child(philos);
		exit(0);
	}
	return (true);
}
