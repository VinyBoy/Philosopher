/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:43:00 by vnieto-j          #+#    #+#             */
/*   Updated: 2023/11/08 17:41:24 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_usleep(long int time_in_ms)
{
	long int	start_time;

	start_time = 0;
	start_time = actual_time();
	while ((actual_time() - start_time) < time_in_ms)
		usleep(time_in_ms / 10);
}

long	int	actual_time(void)
{
	long int		time;
	struct timeval	actual_time;

	time = 0;
	if (gettimeofday(&actual_time, NULL) == -1)
		return (print_error(3), 1);
	time = (actual_time.tv_sec * 1000) + (actual_time.tv_usec / 1000);
	return (time);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int	check_death2(t_philo *philosopher)
{
	pthread_mutex_lock(&philosopher->arg.dead);
	if (philosopher->arg.stop)
	{
		pthread_mutex_unlock(&philosopher->arg.dead);
		return (1);
	}
	pthread_mutex_unlock(&philosopher->arg.dead);
	return (0);
}

void	stop(t_philo *philosopher)
{
	int	i;

	i = -1;
	while (!check_death2(philosopher))
		ft_usleep(1);
	while (++i < philosopher->arg.number_of_philosophers)
		pthread_join(philosopher->philo[i].thread_id, NULL);
	pthread_mutex_destroy(&philosopher->arg.write_mutex);
	i = -1;
	while (++i < philosopher->arg.number_of_philosophers)
		pthread_mutex_destroy(&philosopher->philo[i].fork_letf);
	if (philosopher->arg.stop == 2)
		printf("Each philosopher ate %d times(s)\n",
			philosopher->arg.nb_of_time_each_philo_must_eat);
	free(philosopher->philo);
}
