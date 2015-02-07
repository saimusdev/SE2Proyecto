/*******************************************************************************

File: delay.c

Author: Simon Ortego Parra

*******************************************************************************/
#include <stdio.h>
#include <time.h>

#include "ts_util.h"


void calc (struct timespec ms) 
{
    struct timespec now, end;

    clock_gettime(CLOCK_REALTIME, &now);   
    end = tsAdd(now, ms);

    while (tsCompare(now, end) != 1) {
        clock_gettime(CLOCK_REALTIME, &now);
    }

#ifdef DEBUG 
    time_t delay_millis, delay_millis_fract, elapsed_millis, elapsed_millis_fract;

    clock_gettime (CLOCK_THREAD_CPUTIME_ID, &now);

    tsConvertToMs(ms, &delay_millis, &delay_millis_fract);
    tsConvertToMs(now, &elapsed_millis, &elapsed_millis_fract);

    printf("delay call: %ld.%ld ms\n", delay_millis, delay_millis_fract);
    printf("time elapsed: %ld.%ld ms\n", elapsed_millis, elapsed_millis_fract);
#endif

}


