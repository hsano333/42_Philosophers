/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 22:59:19 by hsano             #+#    #+#             */
/*   Updated: 2022/09/25 23:26:02 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include "stdlib.h"
# include "stdbool.h"
# include "limits.h"

typedef struct s_philo
{
	int philo_num;
	int time_die;
	int time_eat;
	int time_slp;
	int must_eat_num;
}	t_philo;

t_philo	*init_philo(int argc, char **argv);

#endif
