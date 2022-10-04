/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 21:32:05 by hsano             #+#    #+#             */
/*   Updated: 2022/10/05 01:24:26 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philos	*philos;
	pid_t		pid;
	int			status;
	int	i;
	//int	status;

	i = 0;
	pid = fork();
	if (pid < 0)
		return (1);
	else if (pid == 0)
	{
		philos = init_philos(argc, argv);
		if (!philos)
			return (1);
		create_notice_process(philos);
		if (philos->np_pid == 0)
		{
			create_thread_for_process(philos);
			//printf("before waitpid No.1 philos->pp_pidi = %d\n",philos->pp_pid);
			//waitpid(philos->pp_pid, 0 , 0);
			while (i < philos->num)
			{
			//	printf("before waitpid i=%d philos->n_pidi = %d\n",i, philos->mans[i].n_pid);
				waitpid(philos->mans[i].n_pid, &status, 0);
				i++;

			}

			//printf("after waitpid No.2\n");
			//create_process(philos);
			clear_all(philos);
		}
		else 
			waitpid(philos->np_pid, &status, 0);
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		//if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			//kill_process(0, NULL, NULL);
	}
	return (0);
}
