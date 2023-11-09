/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:18:16 by vnieto-j          #+#    #+#             */
/*   Updated: 2023/11/09 18:41:03 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	meal_finish(t_data *data)
{
	pthread_mutex_lock(&data->mutexdead);
	data->death = 1;
	pthread_mutex_unlock(&data->mutexdead);
}

void	is_dead(t_philo *philo, t_data *data, int i)
{
	pthread_mutex_lock(&data->mutexdead);
	data->death = 1;
	pthread_mutex_unlock(&data->mutexdead);
	pthread_mutex_lock(&philo->data->print);
	printf("%08ld %lu is dead\n",
		right_time(data->start), philo[i].philo_id);
	pthread_mutex_unlock(&philo->data->print);
}

int	check_death(t_data *data)
{
	int	dead;

	dead = 0;
	pthread_mutex_lock(&data->mutexdead);
	dead = data->death;
	pthread_mutex_unlock(&data->mutexdead);
	return (dead);
}

int	check_death_meals(t_data *data, t_philo *philo)
{
	unsigned long	i;
	long			time;

	while (1)
	{
		i = -1;
		while (++i < data->nb_philo)
		{
			pthread_mutex_lock(&philo[i].meal);
			time = gettime() - philo[i].last_meal;
			pthread_mutex_unlock(&philo[i].meal);
			if (time > data->ttdie)
				return (is_dead(philo, data, i), 1);
			pthread_mutex_lock(&data->finish_philo);
			if (data->finish == data->nb_philo)
			{
				meal_finish(data);
				pthread_mutex_unlock(&data->finish_philo);
				return (1);
			}
			pthread_mutex_unlock(&data->finish_philo);
		}
		usleep(100);
	}
}