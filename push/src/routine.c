/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:16:08 by vnieto-j          #+#    #+#             */
/*   Updated: 2023/11/08 17:40:31 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	threading(t_philo *philospher)
{
	int	i;

	i = 0;
	while (i < philospher->arg.number_of_philosophers)
	{
		philospher->philo[i].pa = &philospher->arg;
		if (pthread_create(&philospher->philo[i].thread_id, NULL,
				start_routine, &philospher->philo[i]) != 0)
			return (print_error(2), 1);
		i++;
	}
	return (1);
}

void	*start_routine(void *data)
{
	t_philo_thread	*p;

	p = (t_philo_thread *)data;
	if (p->id % 2 == 0)
		ft_usleep(p->pa->time_to_eat / 10);
	while (!check_death(p, 0))
	{
		pthread_create(&p->thread_death_id, NULL, is_dead, data);
		activity(p);
		pthread_detach(p->thread_death_id);
		if ((int)++p->meals_eaten == p->pa->nb_of_time_each_philo_must_eat)
		{
			pthread_mutex_lock(&p->pa->finish);
			p->finish = 1;
			p->pa->nb_of_philo_finish++;
			if (p->pa->nb_of_philo_finish == p->pa->number_of_philosophers)
			{
				pthread_mutex_unlock(&p->pa->finish);
				check_death(p, 2);
			}
			pthread_mutex_unlock(&p->pa->finish);
			return (NULL);
		}
	}
	return (NULL);
}

void	*is_dead(void	*data)
{
	t_philo_thread	*philosopher;

	philosopher = (t_philo_thread *)data;
	ft_usleep(philosopher->pa->time_to_die + 1);
	pthread_mutex_lock(&philosopher->pa->time_eat);
	pthread_mutex_lock(&philosopher->pa->finish);
	if (!check_death(philosopher, 0) && !philosopher->finish
		&& ((actual_time() - philosopher->ms_eat)
			>= (long)(philosopher->pa->time_to_die)))
	{
		pthread_mutex_unlock(&philosopher->pa->time_eat);
		pthread_mutex_unlock(&philosopher->pa->finish);
		pthread_mutex_lock(&philosopher->pa->write_mutex);
		write_status("died\n", philosopher);
		pthread_mutex_unlock(&philosopher->pa->write_mutex);
		check_death(philosopher, 1);
	}
	pthread_mutex_unlock(&philosopher->pa->time_eat);
	pthread_mutex_unlock(&philosopher->pa->finish);
	return (NULL);
}

int	check_death(t_philo_thread *philosopher, int i)
{
	pthread_mutex_lock(&philosopher->pa->dead);
	if (i)
		philosopher->pa->stop = i;
	if (philosopher->pa->stop == 1)
	{
		pthread_mutex_unlock(&philosopher->pa->dead);
		return (1);
	}
	pthread_mutex_unlock(&philosopher->pa->dead);
	return (0);
}
