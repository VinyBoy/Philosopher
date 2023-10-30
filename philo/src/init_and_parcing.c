/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_parcing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:54:45 by vnieto-j          #+#    #+#             */
/*   Updated: 2023/10/30 15:12:57 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/* 
    fonction qui tcheck tout les char d'un double tableau
*/
int	ft_atoi_ovrflw(const char *string)
{
	int	res;
	int	signe;

	signe = 1;
	res = 0;
	if (ft_strcmp(string, "-2147483648") == 0)
		return (-2147483648);
	if (*string == '-' || *string == '+')
	{
		if (*string == '-')
			signe *= -1;
		string++;
	}
	while (*string >= '0' && *string <= '9')
	{
		if (res > INT_MAX / 10 || (res == INT_MAX / 10
				&& (*string - '0') > INT_MAX % 10))
			print_error(0);
		res = res * 10 + (*string - '0');
		string++;
	}
	return (res * signe);
}

int	is_digit(char **argv, int i, int j)
{
	while(argv[i])
	{
        while (argv[i][j])
        {
		    if (argv[i][j] < '0' && argv[i][j] > '9')
			    return (0);
            j++;
        }
        j = 0;
		i++;
	}
    return (1);
}

/* recuperer les arguments du main

argv[1] = [philo_nb]
argv[2] = [time_die] // // time en ms ou un philo meurt apres avoir manger
argv[3] = [time_eat] // time en ms qu'un philo prend a manger avec 2 fork
argv[4] = [time_sleep] // time en ms qu'un philo doit prendre pour dormir
argv[5] = optionnel[must_eat] // nb de fois au'un philo doit eat

typedef struct  s_philo_config
{
    int                 number_of_philosophers;
    int                 time_to_die;
    int                 time_to_eat;
    int                 time_to_sleep;
    int                 nb_if_time_each_philo_must_eat;
    long long int       last_meal_time;
}   t_philo_config;
*/

/*
    FOnction qui sert a initialiser toute les variables de ma struct
    qui vont etre verouiller a un moment par un mutex
*/
void    init_mutex(t_philo *philosopher)
{
    pthread_mutex_init(&philosopher->arg.write_mutex, NULL);
    pthread_mutex_init(&philosopher->arg.dead, NULL);
    pthread_mutex_init(&philosopher->arg.time_eat, NULL);
    pthread_mutex_init(&philosopher->arg.finish, NULL);
}

int initialize(t_philo *philosopher)
{
    int i;

    i = 0;
    philosopher->arg.start_t = actual_time();
    philosopher->arg.stop = 0;
    philosopher->arg.nb_of_philo_finish = 0;
    init_mutex(philosopher);
    while(i < philosopher->arg.number_of_philosophers)
    {
        philosopher->philo[i].id = i + 1;
        philosopher->philo[i].ms_eat = philosopher->arg.start_t;
        philosopher->philo[i].meals_eaten = 0;
        philosopher->philo[i].finish = 0;
        philosopher->philo[i].fork_right = NULL;
        pthread_mutex_init(&philosopher->philo[i].fork_letf, NULL);
        if (philosopher->arg.number_of_philosophers == 1)
            return (1);
        if (i == philosopher->arg.number_of_philosophers - 1)
            philosopher->philo[i].fork_right = &philosopher->philo[0].fork_letf;
        
        else
            philosopher->philo[i].fork_right = &philosopher->philo[i + 1].fork_letf;
        i++;
    }
    return (1);
}

int parse_args(int argc, char **argv, t_philo *philosopher)
{
    if ((argc != 5 || argv != 6) && is_digit(argv, 1, 0))
    {
        philosopher->arg.number_of_philosophers = ft_atoi_ovrflw(argv[1]);
        philosopher->arg.time_to_die = ft_atoi_ovrflw(argv[2]);
        philosopher->arg.time_to_eat = ft_atoi_ovrflw(argv[3]);
        philosopher->arg.time_to_sleep = ft_atoi_ovrflw(argv[4]);
        if (argc == 6)
            philosopher->arg.nb_of_time_each_philo_must_eat = ft_atoi_ovrflw(argv[5]);
        if (philosopher->arg.number_of_philosophers <= 0 || philosopher->arg.time_to_die <= 0
            || philosopher->arg.time_to_eat <= 0 || philosopher->arg.time_to_sleep <= 0)
            return (1);
        return (0);
    }
    return (1);
}
