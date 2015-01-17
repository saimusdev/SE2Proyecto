/*******************************************************************************

File: delay.c

Author: Simon Ortego Parra

*******************************************************************************/

#include <time.h>

#include "ts_util.h"

void delay_ms (struct timespec ms) 
{
	struct timespec now, end;

    clock_gettime(CLOCK_REALTIME, &now);
    
    end = tsAdd(now, ms);

    while (tsCompare(now, end) != 1) {
    	clock_gettime(CLOCK_REALTIME, &now);
    }

}


