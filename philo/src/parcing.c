/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:54:45 by vnieto-j          #+#    #+#             */
/*   Updated: 2023/11/07 17:32:55 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
    @brief-> fonction qui va parser les arguments du main
    
    @return value -> 1 en cas d'echec / 0 si fonctionnement
    
    @argv ->
            argv[1] = [philo_nb]
            argv[2] = [time_die] // // time en ms ou un philo meurt apres avoir manger
            argv[3] = [time_eat] // time en ms qu'un philo prend a manger avec 2 fork
            argv[4] = [time_sleep] // time en ms qu'un philo doit prendre pour dormir
            argv[5] = optionnel[must_eat] // nb de fois au'un philo doit eat / seulement si 6 arguments

    1) verifie qu'on a bien 5 ou 6 arguments et que tout les digits sont bien des chiffres
    2) On attribue les arguments (sous forme de nombre a notre structure d'arguments avec notre atoi modifier)
    3) On verifie que aucun des arguments est negatifs
    4) Si tout s'est bien passer en return 0/ 1 en cas d'echec
*/

int parse_args(int argc, char **argv, t_philo *philosopher)
{
    if ((argc != 5 || argv != 6) && (is_digit(argv, 1, 0) == 0))
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

/* 
    @brief Atoi modifier qui print une error quand on depasse l'overflow
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

/*
    @brief -> Fonction qui check tout les char d'un double tableau afin de verifier qu;il soit tous des chiffres
*/
int	is_digit(char **argv, int i, int j)
{
	while(argv[i])
	{
        while (argv[i][j])
        {
		    if (argv[i][j] < '0' && argv[i][j] > '9')
			    return (1);
            j++;
        }
        j = 0;
		i++;
	}
    return (0);
}

