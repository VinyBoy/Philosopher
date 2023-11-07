#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int mails = 0;
pthread_mutex_t mutex;

void    *routine()
{
    int i;

    i = 0;
    while (i < 10000000)
    {
        //Le mutex lock et unlock fonctionne comme une sorte de parenthese
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex);
        i++;
    }
    return (NULL);
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    pthread_t   th[8];
    int i;
    pthread_mutex_init(&mutex, NULL);
    i = 0;
    while (i < 8)
    {
        if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
            return (1);
        printf("Thread %d has started\n", i);
        i++;
    }
    i = 0;
    while (i < 8)
    {
        if (pthread_join(th[i], NULL) != 0)
            return (5);
        printf("Thread %d has end execution\n", i);
        i++;
    }
    pthread_mutex_destroy(&mutex);
    printf("Number of mails : %d\n", mails);
    return (0);
}