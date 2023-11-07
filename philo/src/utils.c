/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:43:00 by vnieto-j          #+#    #+#             */
/*   Updated: 2023/11/07 18:49:02 by vnieto-j         ###   ########.fr       */
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