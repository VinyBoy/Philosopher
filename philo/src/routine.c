/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:16:08 by vnieto-j          #+#    #+#             */
/*   Updated: 2023/11/02 15:41:15 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
	@brief-> Fonction de thread, thread qui fonctionne en parallele avec chaque philo
			Pour savoir si celui ci est mort ou non (si il na pas manger dans le delai
			imparti).
*/
void	*is_dead(void	*data)
{
	
}
/*
	@Brief-> Fonction qui check si un philo est mort. Renvoie 1 si mort, 0 si vivant
	
	@params-> Pointeur sur ma strucutre t_philo et un entier i
*/
int	check_death(t_philo_thread *philosopher, int i)
{
	pthread_mutex_lock(&philosopher->pa->dead);
	if (i)
		philosopher->pa->stop = i;
	}



void	*start_routine(void *data)
{
	t_philo_thread		*philosopher;
	
	philosopher = (t_philo_thread *)data;
	//Si le nombre d'id (nombre de philo) est paire alors
	if (philosopher->id % 2 == 0)
		ft_usleep(philosopher->pa->time_eat / 10);
	while (!check_death(philosopher, 0))
	{
		pthread_create(&philosopher->thread_death_id, NULL, is_dead, data) 
	
}

/*
	@brief -> Creer chaque thread pour chaque philo en iterant sur notre structure contentant tout nos philo
	
	@params -> Pointeur sur notre structure de type t_philo

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

	@params -> il va recevoir en argument le temps que prend un philo pour manger
				en params du programme
				
	@fonction usleep -> est une fonction du système pour mettre en pause l'exécution.
						La durée de cette mini-pause est définie comme un dixième de la durée
						totale souhaitée.
						Cela permet de réduire la charge du processeur car il ne
						vérifie pas continuellement la condition de la boucle while.
						
	@fonction actual time
*/
void	ft_usleep(long int time_in_ms)
{
	long int	start_time;
	
	start_time = 0;
	start_time = actual_time();
	while ((actual_time() - start_time) < time_in_ms)
		usleep(time_in_ms / 10);
}

/*
	@brief -> Fonction qui permet de renvoyer le temps en microseconde
*/
long	int	actual_time(void)
{
	long int		time;
	struct timeval	actual_time;
	
	time = 0;
	if (gettimeofday(&actual_time, NULL) == -1)
		return(print_error(3), 1);
	time = (actual_time.tv_sec * 1000) + (actual_time.tv_usec / 1000);
	return (time);
	
}

/*
	@brief -> check si un philo est mort ou non
*/