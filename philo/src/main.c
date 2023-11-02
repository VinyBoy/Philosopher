/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:55:04 by vnieto-j          #+#    #+#             */
/*   Updated: 2023/10/31 17:52:53 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void print_error(int error)
{
	if (error == 0)
		printf("Error bad arguments\n");
	else if(error == 1)
		printf("Allocation fail\n");
	else if (error == 2)
		printf("Bad creation of thread\n");
	else if (error == 3)
		printf("Bad attribution of actual time\n");
	exit(1);
}

int main(int argc, char **argv)
{
	t_philo philosopher;

	//Parcing de notre structure avec les args
	if ((parse_args(argc, argv, &philosopher) == 1))
		return (print_error(0), 1);
	//Allocation en fct du nb de philo
	philosopher.philo = malloc(sizeof(t_philo) * philosopher.arg.number_of_philosophers);
	if (!philosopher.philo)
		return (print_error(1), 1);
	//Initialise
	if (!initialize(&philosopher) || !threading(&philosopher))
	{
		free (philosopher.philo);
		return (0);
	}
	
}
