/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:44:32 by hsano             #+#    #+#             */
/*   Updated: 2022/10/05 02:16:11 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_loop(void *man_arg)
{
	t_man		*man;
	t_philos	*philos;
	//t_time		base;
	//t_time		time;
	//size_t	test_time;

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

void	*philo_process(void *man_arg)
{
	t_man		*man;
	//t_philos	*philos;

	man = (t_man *)man_arg;
	//philos = (t_philos *)man->philos;
	philo_loop(man);

	//if (pthread_create(&man->thread, NULL, philo_loop, man_arg))
	//{
		//kill_process(philos);
		//printf("error create process \n");
	//}
						
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

void	*wait_death_process(void	*arg)
{
	if (arg == NULL)
		exit(0);
	wait(0);
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
		//printf("waitpidx No.1 i=%d, npid=%d\n", i,philos->mans[i].n_pid );
		waitpid(philos->mans[i].n_pid, &status, 0);
		//if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
			//printf("exit end \nWEXITSTATUS(status)=%d\n", WEXITSTATUS(status));
		if (WIFSIGNALED(status) && WTERMSIG(status) == 3)
			break ;
			//printf("signal test 3\n");
		//if (WIFSIGNALED(status)) 
				//printf("signal:%d\n", WTERMSIG(status));
		if (WIFSIGNALED(status) && WTERMSIG(status) == 32)
		{
			printf("end?\n");
			break;
			//continue ;
		}


			//kill_process(0, NULL, NULL);
		//printf("waitpidx No.2 i=%d, npid=%d\n", i,philos->mans[i].n_pid );
		i++;
	}
	//printf("waitpidx No.3 i=%d, npid=%d\n", i,philos->mans[i].n_pid );
	//printf("kill_process No.4\n");
	//kill_process(philos);
	//exit(0);
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
	//printf("philos->sem=%d\n", (int)(*(philos->sem_fd)));
	//philos = (t_philos *)arg;
	//man->pid = fork();
	//if (man->pid < 0)
		//kill_process(philos);
	//else if (man->pid == 0)
	//{
	if (pthread_create(&man->thread, NULL, philo_loop, man))
	{
		//printf("kill_process No.5\n");
		kill_process(philos);
		//printf("error create process \n");
	}
	//philo_loop();
	//philo_process(man);
	check_stop(philos, man->id - 1);
		//exit(0);
	//}
	//else
	//{

	//}
	return (NULL);
}

int	create_thread_for_process(t_philos *philos)
{
	int		i;
	t_time		boot_time;

	i = 0;
	philos->pp_pid = fork();
	if (philos->pp_pid < 0)
	{
	//printf("kill_process No.7\n");
		kill_process(philos);
	}
	else if (philos->pp_pid == 0)
	{
		gettimeofday(&boot_time, NULL);
		philos->boot_time = boot_time;
		while (i < philos->num)
		{
			philos->mans[i].pid = fork();
			if (philos->mans[i].pid < 0)
			{
	//printf("kill_process No.8\n");
				kill_process(philos);
			}
			else if (philos->mans[i].pid == 0)
			{
				man_process(&(philos->mans[i]));
				//printf("child process die No.1\n");
				exit(0);
			}
			i++;
		}
		//printf("child process die No.2\n");
		wait_child(philos);
		//printf("child process die No.3\n");
		exit(0);
	}
	//printf("child process die No.4\n");
	//else
		//waitpid(philos->pp_pid, 0 , 0);
	return (true);
}
