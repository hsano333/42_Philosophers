/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:44:32 by hsano             #+#    #+#             */
/*   Updated: 2022/10/03 15:35:30 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_loop(void *man_arg)
{
	t_man		*man;
	t_philos	*philos;

	man = (t_man *)man_arg;
	philos = (t_philos *)man->philos;
	//printf("philo_loop No.2\n");
	//if (man->id % 2 == 1 && man->id != philos->num)
		//while (get_neighbor_eat_cnt(man) == 0)
			//usleep(50);
	//printf("philo_loop No.3\n");
	//else
		//usleep(100);
	while (1)
	{
		philo_eat(man);
		philo_sleep(man);
		philo_think(man);
		if (get_end_flag(philos))
			exit(1);
	}
	exit(0);
	return (NULL);
}

void	*philo_process(void *man_arg)
{
	t_man		*man;
	t_philos	*philos;

	man = (t_man *)man_arg;
	philos = (t_philos *)man->philos;

	if (pthread_create(&man->thread, NULL, philo_loop, man_arg))
	{
		kill_process(philos);
		printf("error create process \n");
	}
	check_stop(philos, man->id - 1);
						
	//philo_loop(man-> &(philos->mans[i]));
	//philo_process
	return (NULL);
}

void	*wait_process(void	*man_arg)
{
	t_man		*man;
	int			status;

	man = (t_man *)man_arg;
	waitpid(man->n_pid, &status, 0);
	return (NULL);
}

void	wait_child(t_philos *philos)
{
	int		i;
	//int		status;
	void	*ptr;

	i = 0;
	//create_init();
	//printf("wait_child No.1\n");
	while (i < philos->num)
	{
		//printf("wait_child No.2, philos->num:%d\n", philos->num);
		if (pthread_create(&(philos->mans[i].thread), NULL, \
							wait_process, (void *)&(philos->mans[i])))
		i++;
		//printf("wait_child No.3\n");
	}
	i = 0;
	while (i < philos->num)
	{
		//printf("wait_child No.4\n");
		pthread_join(philos->mans[i].thread, &ptr);
		//pthread_detach(philos->mans[i].thread);
		i++;
		//printf("wait_child No.5\n");
	}
	printf("all exit\n");
	printf("all exit\n");
	printf("all exit\n");
	printf("all exit\n");
	kill_process(philos);
	exit(0);
}

/*
void	create_process_for_man(t_man *man)
{
	t_philos	*philos;
	//int			status;

	philos = man->philos;
	//printf("create_process No.2 philos->num=%d, i=%d\n", philos->num, i);
	man->pid = fork();
	if (man->pid < 0)
		kill_process(philos);
	else if (man->pid == 0)
	{
		//philo_loop();
		philo_process(man);
		//exit(1);
	}
	else
	{
		//waitpid(man->pid, &status, NULL);
		//if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			//kill_process(0, NULL, NULL);

	}


}
*/


void	*man_process(void	*arg)
{
	t_man	*man;
	t_philos	*philos;

	man = (t_man *)arg;
	philos = man->philos;
	printf("philos->sem=%d\n", *(philos->sem_fd));
	//philos = (t_philos *)arg;
	man->pid = fork();
	if (man->pid < 0)
		kill_process(philos);
	else if (man->pid == 0)
	{
		//philo_loop();
		philo_process(man);
	}
	return (NULL);
}

int	create_thread_for_process(t_philos *philos)
{
	int		i;
	//pid_t	pid;

	i = 0;
	while (i < philos->num)
	{
		pthread_create(&philos->thread, NULL, man_process, (void *)(&philos));
		i++;
	}
	wait_child(philos);
	return (true);
}
