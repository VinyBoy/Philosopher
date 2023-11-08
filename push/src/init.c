/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:57:07 by vnieto-j          #+#    #+#             */
/*   Updated: 2023/11/08 17:34:55 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	initialize(t_philo *philosopher)
{
	int	i;

	i = 0;
	philosopher->arg.start_t = actual_time();
	philosopher->arg.stop = 0;
	philosopher->arg.nb_of_philo_finish = 0;
	init_mutex(philosopher);
	while (i < philosopher->arg.number_of_philosophers)
	{
		philosopher->philo[i].id = i + 1;
		philosopher->philo[i].ms_eat = philosopher->arg.start_t;
		philosopher->philo[i].meals_eaten = 0;
		philosopher->philo[i].finish = 0;
		philosopher->philo[i].fork_right = NULL;
		pthread_mutex_init(&philosopher->philo[i].fork_letf, NULL);
		if (philosopher->arg.number_of_philosophers == 1)
			return (1);
		if (i == philosopher->arg.number_of_philosophers - 1)
			philosopher->philo[i].fork_right = &philosopher->philo[0].fork_letf;
		else
			philosopher->philo[i].fork_right
				= &philosopher->philo[i + 1].fork_letf;
		i++;
	}
	return (1);
}

void	init_mutex(t_philo *philosopher)
{
	pthread_mutex_init(&philosopher->arg.write_mutex, NULL);
	pthread_mutex_init(&philosopher->arg.dead, NULL);
	pthread_mutex_init(&philosopher->arg.time_eat, NULL);
	pthread_mutex_init(&philosopher->arg.finish, NULL);
}
