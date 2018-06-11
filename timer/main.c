#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

void timer_handler(int signo)
{
    printf("signo: %d\n", signo);
}

void timer_sa_handler(int signo, siginfo_t *si, void *uc)
{
    printf("signo: %d\n", signo);
    // printf("sival_ptr = %p; ", si->si_value.sival_ptr);
    printf("*sival_ptr = 0x%lx\n", (long)*(timer_t *)(si->si_value.sival_ptr));
}

static timer_t timer;
void timer_init(void)
{
    struct sigevent evp;
    struct itimerspec its;
    struct sigaction sa;

    int ret = 0;

    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = timer_sa_handler;
    sigemptyset(&sa.sa_mask);

    ret = sigaction(SIGRTMIN, &sa, NULL);
    if (ret < 0) {
        perror("sigaction error\n");
        return;
    }

    evp.sigev_signo = SIGRTMIN;
    evp.sigev_notify = SIGEV_SIGNAL;
    evp.sigev_value.sival_ptr = &timer;

    // signal(evp.sigev_signo, timer_handler);

    ret = timer_create(CLOCK_REALTIME, &evp, &timer);
    if (ret < 0) {
        perror("timer_create error\n");
        return;
    }
    printf("timer id = 0x%lx\n", (long)timer);

    its.it_value.tv_sec = 1;
    its.it_value.tv_nsec = 0;
    its.it_interval.tv_sec = 1;
    its.it_interval.tv_nsec = 0;

    ret = timer_settime(timer, 0, &its, NULL);
    if (ret < 0) {
        perror("timer_settime error\n");
        return;
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