/*******************************************************************************

File: delay.c

Author: Simon Ortego Parra

*******************************************************************************/

#include <time.h>
#include  <stdio.h>  

#include "ts_util.h"

#ifdef DEBUG 
#	include "pragmatics.h"
#endif

void delay_ms (struct timespec ms) 
{
	struct timespec now, end;

#ifdef DEBUG 
	struct timespec initial, final, elapsed;
	clock_gettime (CLOCK_THREAD_CPUTIME_ID, &initial);
#endif

	clock_gettime(CLOCK_REALTIME, &now);
    
    end = tsAdd(now, ms);

    while (tsCompare(now, end) != 1) {
    	clock_gettime(CLOCK_REALTIME, &now);
    }

#ifdef DEBUG 
    clock_gettime (CLOCK_THREAD_CPUTIME_ID, &final);
    elapsed = tsSubtract (initial, final);
    printf("delay call: %ld.%ld ms\n", elapsed.tv_nsec % NANOS_IN_MILLIS, 
    	elapsed.tv_nsec / NANOS_IN_MILLIS);
	printf("time elapsed: %ld.%ld ms\n", elapsed.tv_nsec % NANOS_IN_MILLIS, 
		elapsed.tv_nsec / NANOS_IN_MILLIS);
#endif

}


