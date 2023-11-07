/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:36:52 by vnieto-j          #+#    #+#             */
/*   Updated: 2023/11/07 19:06:26 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void    activity(t_philo_thread *philospher)
{
    pthread_mutex_lock(&philospher->fork_letf);
    pthread_mutex_lock(&philospher->pa->write_mutex);
    write_status("has taken a fork\n", philospher);
	pthread_mutex_unlock(&philospher->pa->write_mutex);
	if (!philospher->fork_right)
	{
		ft_usleep(philospher->pa->time_to_die * 2);
		return ;
	}
    pthread_mutex_lock(&philospher->fork_right);
	pthread_mutex_lock(&philospher->pa->write_mutex);
    write_status("has taken a fork\n", philospher);
	pthread_mutex_unlock(&philospher->pa->write_mutex);
	pthread_mutex_lock(&philospher->pa->write_mutex);
    write_status("is eating\n", philospher);
	pthread_mutex_lock(&philospher->pa->time_eat);
	philospher->ms_eat = actual_time();
	pthread_mutex_unlock(&philospher->pa->time_eat);
	pthread_mutex_unlock(&philospher->pa->write_mutex);
	ft_usleep(philospher->pa->time_eat);
	pthread_mutex_unlock(&philospher->fork_right);
	pthread_mutex_unlock(&philospher->fork_letf);
	sleep_think(philospher);
}

void	sleep_think(t_philo_thread *philosopher)
{
	pthread_mutex_lock(&philosopher->pa->write_mutex);
	write_status("is sleeping\n", philosopher);
	pthread_mutex_unlock(&philosopher->pa->write_mutex);
	ft_usleep(philosopher->pa->time_to_sleep);
	pthread_mutex_lock(&philosopher->pa->write_mutex);
	write_status("is thinking\n", philosopher);
	pthread_mutex_unlock(&philosopher->pa->write_mutex);
}

void    write_status(char *str, t_philo_thread *philosopher)
{
	long int	time;
	
	time = -1;
	time = actual_time() - philosopher->pa->start_t;
	if (time >= 0 && time <= 2147483647 && !check_death(philosopher, 0))
	{
		printf("%ld ", time);
		printf("Philo %d %s", philosopher->id, str);
	}
}

