/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 21:32:05 by hsano             #+#    #+#             */
/*   Updated: 2022/10/03 14:51:44 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philos	*philos;
	pid_t		pid;
	int			status;

	pid = fork();
	if (pid < 0)
		return (1);
	else if (pid == 0)
	{
		philos = init_philos(argc, argv);
		if (!philos)
			return (1);
		create_notice_process(philos);
		create_thread_for_process(philos);
		//create_process(philos);
		clear_all(philos);
	}
	else
	{
		waitpid(pid, &status, 0);
		//if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			//kill_process(0, NULL, NULL);
	}
	return (0);
}
