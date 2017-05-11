#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h> 
#include <signal.h>
#include <time.h>
void handle(union sigval v)
{
    time_t t;
    char p[32];

    time(&t);
    strftime(p, sizeof(p), "%T", localtime(&t));

    printf("%s thread %lu, val = %d, signal captured.\n", p, pthread_self(), v.sival_int);
    return;
}



int main()
{
    struct sigevent evp;
    struct itimerspec ts;
    timer_t timer;
    int ret;

    printf("thread %lu \n",pthread_self());

    evp.sigev_value.sival_ptr = &timer;
    evp.sigev_notify = SIGEV_SIGNAL;
    evp.sigev_signo = SIGUSR1;
    signal(SIGUSR1, handle);

    ret = timer_create(CLOCK_REALTIME, &evp, &timer);
    if( ret )
        perror("timer_create");

    ts.it_interval.tv_sec = 1;
    ts.it_interval.tv_nsec = 0;
    ts.it_value.tv_sec = 3;
    ts.it_value.tv_nsec = 0;

    ret = timer_settime(timer, 0, &ts, NULL);
    if( ret )
    perror("timer_settime");

//    while(1);
pause();
}
