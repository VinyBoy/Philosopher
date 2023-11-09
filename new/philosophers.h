/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:16:24 by vnieto-j          #+#    #+#             */
/*   Updated: 2023/11/09 18:10:21 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdint.h>
# include <errno.h>
# include <sys/time.h>

typedef struct s_philo
{
	int					left_fork;
	int					right_fork;
	pthread_mutex_t		*mutexlf;
	pthread_mutex_t		*mutexrf;
	pthread_mutex_t		fork;
	pthread_mutex_t		meal;
	unsigned long		philo_id;
	struct s_data		*data;
	int					nb_meals;
	long				last_meal;
}	t_philo;

typedef struct s_data
{
	pthread_mutex_t		mutexdead;
	pthread_mutex_t		mutexmeals;
	pthread_mutex_t		finish_philo;
	pthread_mutex_t		print;
	unsigned long		nb_philo;
	t_philo				*philo;
	unsigned long		finish;
	int					ttdie;
	int					tteat;
	int					ttthink;
	int					ttsleep;
	int					max_meals;
	int					death;
	unsigned long		start;
}	t_data;

/*Lib*/
long	ft_atoi(const char *str);
void	*ft_calloc(size_t elementCount, size_t elementSize);
int		ft_isdigit(int c);
void	*ft_memset(void *s, int c, size_t n);
/*Initialization*/
int		init_data(t_data *data, int argc, char **argv);
void	init_tdata(t_data *tdata, t_data *data);
int		init_philo(t_data *data);
void	init_each_philo(t_philo *philo, t_data *data);
/*Actions*/
int		eat(t_data *data, t_philo *philo);
int		resting(t_data *data, t_philo *philo);
int		thinking(t_philo *philo);
int		die(t_data *data);
int		forks(t_data *data);
int		pickup_leftfork(t_philo *philo);
int		pickup_rightfork(t_philo *philo);
/*Time*/
long	gettime(void);
int		ft_usleep(t_data *data, long ms);
long	right_time(long delay);
long	time_to_die(long delay);
void	set_start_time(t_data *data);
/*Others*/
int		print_state(t_philo *philo, char *str);
int		check_death(t_data *data);
int		check_death_meals(t_data *data, t_philo *philo);

/*
si le NOMBRE PHILO EST PAIR
	sum(tteat + ttsleep) * 2 > ttdie ILS VIVENT
else
	ILS DIENT

si le NOMBRE PHILO EST IMPAIR
	sum(tteat + ttsleep) * 3 > ttdie ILS VIVENT
else
	ILS DIENT
*/

#endif