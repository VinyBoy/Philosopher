/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:18:32 by vnieto-j          #+#    #+#             */
/*   Updated: 2023/11/09 18:41:08 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	left_right(t_philo *philo)
{
	pthread_mutex_lock(philo->mutexlf);
	if (print_state(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(philo->mutexlf);
		return (1);
	}
	pthread_mutex_lock(philo->mutexrf);
	if (print_state(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(philo->mutexlf);
		pthread_mutex_unlock(philo->mutexrf);
		return (1);
	}
	return (0);
}

int	right_left(t_philo *philo)
{
	pthread_mutex_lock(philo->mutexrf);
	if (print_state(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(philo->mutexrf);
		return (1);
	}
	pthread_mutex_lock(philo->mutexlf);
	if (print_state(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(philo->mutexrf);
		pthread_mutex_unlock(philo->mutexlf);
		return (1);
	}
	return (0);
}

int	take_forks(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		if (left_right(philo))
			return (1);
	}
	else
	{
		if (right_left(philo))
			return (1);
	}
	return (print_state(philo, "is eating"));
}

int	resting(t_data *data, t_philo *philo)
{
	if (print_state(philo, "is sleeping"))
		return (1);
	if (ft_usleep(data, data->ttsleep))
		return (1);
	return (0);
}

int	eat(t_data *data, t_philo *philo)
{	
	if (take_forks(philo))
		return (1);
	if (ft_usleep(data, data->tteat))
	{
		pthread_mutex_unlock(philo->mutexlf);
		pthread_mutex_unlock(philo->mutexrf);
		return (1);
	}
	pthread_mutex_unlock(philo->mutexlf);
	pthread_mutex_unlock(philo->mutexrf);
	pthread_mutex_lock(&philo->meal);
	philo->last_meal = gettime();
	pthread_mutex_unlock(&philo->meal);
	philo->nb_meals++;
	if (philo->nb_meals == philo->data->max_meals)
	{
		pthread_mutex_lock(&philo->data->finish_philo);
		philo->data->finish++;
		pthread_mutex_unlock(&philo->data->finish_philo);
		return (1);
	}
	return (0);
}
