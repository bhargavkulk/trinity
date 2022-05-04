#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>
#include "common.hpp"

extern void time_handler();

static bool sendTicks = true;
void stop_timer()
{
    sendTicks = false;
}

// framerate > 1
void *tick(void *args)
{
    struct timespec req_time;
    req_time.tv_sec = 0;

    struct timeval t;
    while(sendTicks)
    {
        gettimeofday(&t, NULL);
        req_time.tv_nsec = (MUS_PER_FRAME - (t.tv_usec % MUS_PER_FRAME)) * 1000;
        nanosleep(&req_time, NULL);
        time_handler();
    }

    pthread_exit((void*) 0);
}