/*******************************************************************************

File: ts_util.c

Author: Alex Measday
        Simon Ortego Parra
        
*******************************************************************************/

#include  <time.h>

struct  timespec  tsAdd (struct  timespec  time1, struct  timespec  time2)
{   
/* Local variables. */
    struct  timespec  result ;

/* Add the two times together. */

    result.tv_sec = time1.tv_sec + time2.tv_sec ;
    result.tv_nsec = time1.tv_nsec + time2.tv_nsec ;
    if (result.tv_nsec >= 1000000000L) {        /* Carry? */
        result.tv_sec++ ;  result.tv_nsec = result.tv_nsec - 1000000000L ;
    }

    return (result) ;

}

int  tsCompare (struct  timespec  time1, struct  timespec  time2)
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

