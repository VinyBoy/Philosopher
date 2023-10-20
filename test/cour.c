/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cour.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:25:50 by vnieto-j          #+#    #+#             */
/*   Updated: 2023/10/05 16:46:28 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>

#define TIMES_TO_COUNT 21000

#define NC	"\e[0m"
#define YELLOW	"\e[33m"
#define BYELLOW	"\e[1;33m"
#define RED	"\e[31m"
#define GREEN	"\e[32m"

typedef struct s_counter
{
    pthread_mutex_t count_mutex;
    unsigned int    count;
} t_counter;

void    *thread_routine(void *data)
{
    //Chaque thread commence ici
    pthread_t       tid;
    t_counter       *counter; // ptr vers la stuct dans le main
    unsigned int    i;

    tid = pthread_self();
    counter = (t_counter *)data;
    //on imprime avant que le thread itere 
	//	Pour lire la valeur de count on verouille le mutex
	pthread_mutex_lock(&counter->count_mutex);
    printf("%sThread [%ld]: compte au depar = %u.%s\n", YELLOW, tid, counter->count, NC);\
	pthread_mutex_unlock(&counter->count_mutex);
    i = 0;
    while (i < TIMES_TO_COUNT)
    {
        //on itere Times_to_count fois
		//on verrouille le ;utex le temps d incrementer le compte
		pthread_mutex_lock(&counter->count_mutex);
		counter->count++;
		pthread_mutex_unlock(&counter->count_mutex);
        i++;
    }
    // print le compte final ou le thread a terminer le compte
    printf("%sThread [%ld]: Compte final = %u.%s\n",YELLOW, tid, counter->count, NC);
    return (NULL); //Thread se termine ici
}

int main(void)
{
    pthread_t   tid1;
    pthread_t   tid2;
    //vrbl pour tenir le compte des 2 threads
    t_counter counter;

    counter.count = 0;
	
	//Initialisation du mutex
	pthread_mutex_init(&counter.count_mutex, NULL);
	
    //On attend que le compte final soit 2 * times_to_count
    printf("Main : le compte attendu est de %s%u%s\n", GREEN, 2 * TIMES_TO_COUNT, NC);
    
    //Creation des threads
    pthread_create(&tid1, NULL, thread_routine, &counter);
    printf("Main: Creation du premier thread [%ld]\n", tid1);
    pthread_create(&tid2, NULL, thread_routine, &counter);
    printf("Main: Creation du second thread [%ld]\n", tid2);

    //Recuperation des threads
    pthread_join(tid1, NULL);
    printf("Main: Union du premier thread [%ld]\n", tid1);
    pthread_join(tid2, NULL);
    printf("Main: Union du second thread [%ld]\n", tid2);
    
    //Evaluation du compte final
	if (counter.count != (2 * TIMES_TO_COUNT))
		printf("%sMain: ERREUR ! Le compte est de %u%s\n", RED, counter.count, NC);
	else
		printf("%sMain: OK. Le compte est d e %u%s\n", GREEN, counter.count, NC);
	//detruire le mutex a la fin
	pthread_mutex_destroy(&counter.count_mutex);
	return (0);
}