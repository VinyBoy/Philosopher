/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:17:32 by vnieto-j          #+#    #+#             */
/*   Updated: 2023/11/09 18:40:46 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	gettime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long	right_time(long delay)
{
	return (gettime() - delay);
}

void	set_start_time(t_data *data)
{
	size_t	i;

	data->start = gettime();
	i = -1;
	while (++i < data->nb_philo)
		data->philo[i].last_meal = gettime();
}

int	thinking(t_philo *philo)
{
	if (!philo->data->nb_philo % 2 == 0)
	{
		ft_usleep(philo->data, philo->data->tteat * 2
			- philo->data->ttsleep);
	}
	return (print_state(philo, "is thinking"));
}