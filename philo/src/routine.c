/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:16:08 by vnieto-j          #+#    #+#             */
/*   Updated: 2023/10/30 17:50:51 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*start_routine(void *data)
{
	t_philo_thread		*philosopher;
	
	philosopher = (t_philo *)data;
	if (philosopher->id % 2 == 0)
		ft_usleep()
}

/*
	Creation des thread pour chaque philo
	On va parcourir dans la strucutre arg de philo en philo
	Chaque philo va recuperer via philo[i].pa les arg du programme
	Ce qui va permettre de lui fournir les details necessaire
	avec pthread_create on va donc creer chaque thread poru chaque philo
*/
int	threading(t_philo *philospher)
{
	int	i;
	
	i = 0;
	while(i < philospher->arg.number_of_philosophers)
	{
		philospher->philo[i].pa = &philospher->arg;
		if (pthread_create(&philospher->philo[i].thread_id, NULL,
			start_routine, &philospher->philo[i]) != 0)
			return (print_error(2), 1);
		i++;
	}
	return (1);
}

/*
	@brief -> Fonction qui va permettre de mettre le programme en pause pendant un temps
			specifier en miliseconde

	@params _> il va recevoir en argument le temps que prend un philo pour manger
				en params du programme
*/
void	ft_usleep(long int time_in_ms)
{
	long int	start_time;
	
	start_time = 0;
	start_time = actual_time();
	while ((actual_time() - start_time) < time_in_ms)
		usleep(time_in_ms / 10);
}