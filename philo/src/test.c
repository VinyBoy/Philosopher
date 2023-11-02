#include <sys/time.h>
#include <stdio.h>

long int actual_time(void)
{
    long int time;
    struct timeval actual_time;

    time = 0;
    gettimeofday(&actual_time, NULL);
    //conversion en milliseconde
    return(actual_time.tv_sec * 1000 + actual_time.tv_usec / 1000);
}

int main()
{
    printf("temps actuel %ld ms\n", actual_time());
}