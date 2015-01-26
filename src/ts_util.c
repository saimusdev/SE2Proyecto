/*******************************************************************************

File: ts_util.c

Author: Alex Measday
        Simon Ortego Parra
        
*******************************************************************************/

#include  <time.h>
#include "ts_util.h"
        
#ifdef DEBUG
#include  <stdio.h>         
#include  <string.h>         

#include "pragmatics.h"
#endif

struct timespec tsAdd (struct timespec time1, struct timespec time2)
{   
/* Local variables. */
    struct timespec result ;

/* Add the two times together. */

    result.tv_sec = time1.tv_sec + time2.tv_sec ;
    result.tv_nsec = time1.tv_nsec + time2.tv_nsec ;
    if (result.tv_nsec >= 1000000000L) {        /* Carry? */
        result.tv_sec++ ;  result.tv_nsec = result.tv_nsec - 1000000000L ;
    }

    return (result) ;

}

int tsCompare (struct timespec time1, struct timespec time2)
{

    if (time1.tv_sec < time2.tv_sec)
        return (-1) ;               /* Less than. */
    else if (time1.tv_sec > time2.tv_sec)
        return (1) ;                /* Greater than. */
    else if (time1.tv_nsec < time2.tv_nsec)
        return (-1) ;               /* Less than. */
    else if (time1.tv_nsec > time2.tv_nsec)
        return (1) ;                /* Greater than. */
    else
        return (0) ;                /* Equal. */

}

void tsConvertToMs (struct timespec time, time_t *millis, time_t *millis_fract)
{
/* Local variables  */

    if(time.tv_sec != 0) {
        *millis = time.tv_sec * MILLIS_IN_ONE_SEC;
    } else {
        *millis = 0;
    }
    if(time.tv_nsec != 0) {
        *millis += time.tv_nsec / NANOS_IN_MILLIS;
        *millis_fract = time.tv_nsec % NANOS_IN_MILLIS;
    }
}

