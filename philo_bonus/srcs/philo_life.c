/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:13:31 by hsano             #+#    #+#             */
/*   Updated: 2022/10/04 04:00:43 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
static void	philo_eat_odd(t_man *man)
{
	t_philos        *philos;

	philos = (t_philos *)man->philos;
	if (get_end_flag(philos))
		return ;
	pthread_mutex_lock(man->mutex_left);
	put_logs(man, FORKS);
	pthread_mutex_lock(man->mutex_right);
	put_logs(man, FORKS);
	set_eat_time(man);
	increment_eat_cnt(man);
	put_logs(man, EAT);
	helper_sleep(philos->time_eat);
	increment_eat_cnt(man);
	pthread_mutex_unlock(man->mutex_right);
	pthread_mutex_unlock(man->mutex_left);
}
*/

void	philo_eat_even(t_man *man)
{
	t_philos	*philos;

	philos = (t_philos *)man->philos;
	if (get_end_flag(philos))
		return ;
	/*
	pthread_mutex_lock(man->mutex_right);
	put_logs(man, FORKS);
	pthread_mutex_lock(man->mutex_left);
	put_logs(man, FORKS);
	set_eat_time(man);
	increment_eat_cnt(man);
	put_logs(man, EAT);
	helper_sleep(philos->time_eat);
	increment_eat_cnt(man);
	pthread_mutex_unlock(man->mutex_left);
	pthread_mutex_unlock(man->mutex_right);
	*/
}

void	philo_eat(t_man *man, t_philos *philos)
{
	//t_philos	*philos;


	//printf("philo_eat No.1\n");
	//philos = (t_philos *)man->philos;
	//printf("philo_eat No.2\n");
	if (get_end_flag(philos))
	{
		//printf("philo_eat No.2 - 1\n");
		return ;
	}
	//kill()
	//printf("philo_eat No.3, philos->sem_fd=%p\n", philos->sem_fd);
	sem_wait(philos->sem_fd);
	//printf("philo_eat No.4\n");
	put_logs(man, FORKS);
	//printf("philo_eat No.5\n");
	sem_wait(philos->sem_fd);
	//printf("philo_eat No.6\n");
	put_logs(man, FORKS);
	//printf("philo_eat No.7\n");
	set_eat_time(man);
	put_logs(man, EAT);
	helper_sleep(philos->time_eat);
	increment_eat_cnt(man);
	sem_post(philos->sem_fd);
	sem_post(philos->sem_fd);

	/*
	if (man->id % 2 == 0)
		philo_eat_even(man);
	else
		philo_eat_odd(man);
	*/
}

void	philo_sleep(t_man *man, t_philos *philos)
{
	//t_philos	*philos;

	//philos = (t_philos *)man->philos;
	if (get_end_flag(philos))
		return ;
	put_logs(man, SLEEP);
	helper_sleep(philos->time_slp);
}

void	think_sleep(t_man *man, size_t sleep_time, t_philos *philos)
{
	//t_philos	*philos;
	//size_t	time;
	//t_time	time;
	//size_t	time_since_eat;

	//time = 
	//if (time > time_since_eat)
	//gettimeofday(&time, NULL);
	//time_since_eat = diff_time(time, man->timestamp_eating);

	//philos = (t_philos *)man->philos;
	//if (time_since_eat > (size_t)philos->time_die * 1000)
	if ((philos->num % 2 == 0) && ((int)(man->cnt_eat % 2) == (man->id % 2)))
	{
		if (man->cnt_eat == 0)
			helper_sleep(sleep_time);
	}
	else if (philos->num % 2 == 1)
	{
		if (((int)(man->cnt_eat % 3) == (man->id % 3)))
			helper_sleep(sleep_time);
		/*
		if (man->id <= 3)
		{
			if ((int)(man->cnt_eat % 3) != man->id % 3)
				helper_sleep(sleep_time);
		}
		else
		{
			if ((philos->num % 2 == 0) && (int)man->cnt_eat % 2 == man->id % 2)
				helper_sleep(sleep_time);

		}
		*/
		////else if (philos->num % 2 == 0 && philos->cnt_eat % 2 == philos->id % 2)
			//helper_sleep(sleep_time);


	}
}

void	philo_think(t_man *man, t_philos *philos)
{
	//t_philos	*philos;
	t_time	time;
	size_t	time_since_eat;
	size_t	wait_time;

	gettimeofday(&time, NULL);
	time_since_eat = diff_time(time, man->timestamp_eating);
	//philos = (t_philos *)man->philos;
	wait_time = (size_t)((philos->time_eat + philos->time_slp) / 10);

	put_logs(man, THINK);
	if (time_since_eat > wait_time)
		think_sleep(man, wait_time, philos);

	//while (get_eat_cnt(man) > get_neighbor_eat_cnt(man))
	//if (get_eat_cnt(man) / 2 > get_neighbor_eat_cnt(man) / 2)
	//{
		//helper_sleep(philos->time_eat / 2);
		//printf("man id=%d, think\n", man->id);
		//helper_sleep(10);
	//}
	if (get_end_flag(philos))
		return ;
}
