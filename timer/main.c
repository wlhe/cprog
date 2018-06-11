#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

void timer_handler(int signo)
{
    printf("signo: %d\n", signo);
}

void timer_init(void)
{
    timer_t timer;
    struct sigevent evp;
    struct itimerspec its;
    int ret = 0;

    evp.sigev_signo = SIGUSR1;
    evp.sigev_notify = SIGEV_SIGNAL;
    evp.sigev_value.sival_ptr = &timer;

    signal(evp.sigev_signo, timer_handler);

    ret = timer_create(CLOCK_REALTIME, &evp, &timer);
    if (ret < 0) {
        perror("timer_create error\n");
        return;
    }

    its.it_value.tv_sec = 1;
    its.it_value.tv_nsec = 0;
    its.it_interval.tv_sec = 1;
    its.it_interval.tv_nsec = 0;

    ret = timer_settime(timer, 0, &its, NULL);
    if (ret < 0) {
        perror("timer_settime error\n");
    }
}

int main(int argc, char **argv)
{
    timer_init();

    while (1) {
        usleep(1000);
    }
    return 1;
}