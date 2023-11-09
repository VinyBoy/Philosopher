/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:16:41 by vnieto-j          #+#    #+#             */
/*   Updated: 2023/11/09 18:41:00 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_each_philo(t_philo *philo, t_data *data)
{
	unsigned long	i;

	i = 0;
	while (i < data->nb_philo)
	{
		philo[i].data = data;
		philo[i].philo_id = i + 1;
		pthread_mutex_init(&philo[i].fork, NULL);
		pthread_mutex_init(&philo[i].meal, NULL);
		philo[i].mutexlf = &philo[i].fork;
		if (i == data->nb_philo - 1)
			philo[i].mutexrf = &philo[0].fork;
		else
			philo[i].mutexrf = &philo[i + 1].fork;
		i++;
	}
}

int	check_args(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
			if (ft_isdigit(argv[i][j]) != 1)
				return (-1);
	}
	return (0);
}

int	init_data(t_data *data, int argc, char **argv)
{
	if (check_args(argv) == -1)
		return (-1);
	memset(data, 0, sizeof(&data));
	data->nb_philo = ft_atoi(argv[1]);
	data->ttdie = ft_atoi(argv[2]);
	data->tteat = ft_atoi(argv[3]);
	data->ttsleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		data->max_meals = ft_atoi(argv[5]);
	}
	pthread_mutex_init(&data->mutexmeals, NULL);
	pthread_mutex_init(&data->finish_philo, NULL);
	pthread_mutex_init(&data->print, NULL);
	return (0);
}