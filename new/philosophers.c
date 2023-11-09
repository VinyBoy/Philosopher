/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:17:10 by vnieto-j          #+#    #+#             */
/*   Updated: 2023/11/09 18:40:54 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	join_threads(t_data *data, pthread_t *threads)
{	
	unsigned long	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_join(threads[i], NULL) != 0)
			return (printf("ERROR joining thread #%lu\n", i + 1), 1);
		i++;
	}
	return (0);
}

void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->data->nb_philo == 1)
	{
		pthread_mutex_lock(philo->mutexlf);
		if (print_state(philo, "has taken a fork"))
			return (NULL);
		pthread_mutex_unlock(philo->mutexlf);
		return (NULL);
	}
	if ((philo -> philo_id % 2))
		ft_usleep(philo->data, philo->data->tteat / 10);
	while (1)
	{
		if (philo->nb_meals && philo -> data->nb_philo % 2)
			ft_usleep(philo->data, 0.25 * philo->data->tteat);
		if (eat(philo->data, philo) == 1)
			break ;
		if (resting(philo->data, philo) == 1)
			break ;
		if (thinking(philo) == 1)
			break ;
	}
	return (0);
}

int	init_philo(t_data *data)
{
	unsigned long	i;
	t_philo			*philo;
	pthread_t		*threads;

	threads = malloc(data->nb_philo * sizeof(pthread_t));
	if (!threads)
		return (-1);
	philo = ft_calloc(data->nb_philo, sizeof(t_philo));
	if (!philo)
		return (free(threads), -1);
	init_each_philo(philo, data);
	data->philo = philo;
	set_start_time(data);
	i = -1;
	while (++i < data->nb_philo)
	{
		if (pthread_create(&threads[i], NULL,
				start_routine, (void *)&philo[i]) != 0)
			return (printf("ERROR creating thread #%lu\n", i + 1),
				free(threads), -1);
	}
	(check_death_meals(data, philo));
	join_threads(data, threads);
	return (free(threads), free(philo), 0);
}

int	main(int argc, char **argv)
{
	static t_data	data = {0};

	if (argc != 5 && argc != 6)
		return (printf("Wrong number of arguments\n"), -1);
	if (init_data(&data, argc, argv) != 0)
		return (printf("Failed to initialize data\n"), -1);
	init_philo(&data);
	return (0);
}
