# ifndef    PHILO_H
#  define  PHILO_H



#include "../Ft_printf/ft_printf.h"
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct  s_philo_thread
{
    int                 id;
    pthread_t           thread_id;
    pthread_t           thread_death_id;
    pthread_mutex_t     fork_letf;
    pthread_mutex_t     *fork_right;
    //t_arg             *pa;
    long int            ms_eat;
    unsigned int        meals_eaten;
    int                 finish;
}   t_philo_thread;

typedef struct  s_philo_arg
{
    int                 number_of_philosophers;
    int                 time_to_die;
    int                 time_to_eat;
    int                 time_to_sleep;
    int                 nb_of_time_each_philo_must_eat;
	long int			start_t;
    pthread_mutex_t     write_mutex;
    pthread_mutex_t     dead;
    pthread_mutex_t     time_eat;
    pthread_mutex_t     finish;
    int                 stop;
    int                 nb_of_philo_finish;
    
}   t_philo_arg;

typedef struct s_philo
{
    t_philo_thread		*philo;
    t_philo_arg			arg;
}   t_philo;

/*
    Init_and_parcing.c
*/
int	    ft_atoi_ovrflw(const char *string);
int		is_digit(char **argv, int i, int j);
void    init_mutex(t_philo *philosopher);
int     initialize(t_philo *philosopher);
int 	parse_args(int argc, char **argv, t_philo *philosopher);

/*
    main.c
*/
void    print_error(int error);
int     main(int argc, char **argv);

/*
    routine.c
*/

#endif