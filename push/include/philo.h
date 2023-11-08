/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:17:40 by vnieto-j          #+#    #+#             */
/*   Updated: 2023/11/08 18:37:45 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef    PHILO_H
# define  PHILO_H

# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_philo_arg
{
	int					number_of_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_of_time_each_philo_must_eat;
	long int			start_t;
	pthread_mutex_t		write_mutex;
	pthread_mutex_t		dead;
	pthread_mutex_t		time_eat;
	pthread_mutex_t		finish;
	int					stop;
	int					nb_of_philo_finish;
}	t_philo_arg;

typedef struct s_philo_thread
{
	int					id;
	pthread_t			thread_id;
	pthread_t			thread_death_id;
	pthread_mutex_t		fork_left;
	pthread_mutex_t		*fork_right;
	t_philo_arg			*pa;
	long int			ms_eat;
	unsigned int		meals_eaten;
	int					finish;
}	t_philo_thread;

typedef struct s_philo
{
	t_philo_thread		*philo;
	t_philo_arg			arg;
}	t_philo;

/*
    Init_and_parcing.c
*/
int			ft_atoi_ovrflw(const char *string);
int			is_digit(char **argv, int i, int j);
void		init_mutex(t_philo *philosopher);
int			initialize(t_philo *philosopher);
int			parse_args(int argc, char **argv, t_philo *philosopher);
/*
    main.c
*/
int			check_death2(t_philo *philosopher);
void		print_error(int error);
void		stop(t_philo *philosopher);
/*
    routine.c
*/
int			threading(t_philo *philospher);
void		*start_routine(void *data);
void		*is_dead(void	*data);
int			check_death(t_philo_thread *philosopher, int i);
/*
    activity.c
*/
void		write_status(char *str, t_philo_thread *philosopher);
void		sleep_think(t_philo_thread *philosopher);
void		activity(t_philo_thread *philospher);
/*
    utils.c
*/
void		ft_usleep(long int time_in_ms);
long int	actual_time(void);
int			ft_strcmp(const char *s1, const char *s2);

#endif