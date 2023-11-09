/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:17:46 by vnieto-j          #+#    #+#             */
/*   Updated: 2023/11/09 18:40:50 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	print_state(t_philo *philo, char *str)
{
	if (check_death(philo->data))
		return (1);
	pthread_mutex_lock(&philo->data->print);
	printf("%08ld %lu %s\n",
		right_time(philo->data->start), philo->philo_id, str);
	pthread_mutex_unlock(&philo->data->print);
	return (0);
}