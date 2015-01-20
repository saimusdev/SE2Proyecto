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

#ifdef DEBUG
struct  timespec  tsSubtract (struct  timespec  time1, struct  timespec  time2)
{   
/* Local variables.  */
    struct  timespec  result ;

/* Subtract the second time from the first.  */

    if ((time1.tv_sec < time2.tv_sec) ||
        ((time1.tv_sec == time2.tv_sec) &&
         (time1.tv_nsec <= time2.tv_nsec))) {       /* TIME1 <= TIME2?  */
        result.tv_sec = result.tv_nsec = 0 ;
    } else {                        /* TIME1 > TIME2  */
        result.tv_sec = time1.tv_sec - time2.tv_sec ;
        if (time1.tv_nsec < time2.tv_nsec) {
            result.tv_nsec = time1.tv_nsec + 1000000000L - time2.tv_nsec ;
            result.tv_sec-- ;               /* Borrow a second.  */
        } else {
            result.tv_nsec = time1.tv_nsec - time2.tv_nsec ;
        }
    }

    return (result) ;
}

const  char  *tsShow (struct  timespec  binaryTime, bool  inLocal, const  char  *format)
{    
/* Local variables.  */
    struct  tm  calendarTime ;
#define  MAX_TIMES  4
    static  char  asciiTime[MAX_TIMES][64] ;
    static  int  current = 0 ;



/* Convert the TIMESPEC to calendar time: year, month, day, etc.  */
    if (inLocal)
        calendarTime = *(localtime ((time_t *) &binaryTime.tv_sec)) ;
    else
        calendarTime = *(gmtime ((time_t *) &binaryTime.tv_sec)) ;

/* Format the time in ASCII. */

    current = (current + 1) % MAX_TIMES ;

    if (format == NULL) {
        strftime (asciiTime[current], 64, "%Y-%j-%H:%M:%S", &calendarTime) ;
        sprintf (asciiTime[current] + strlen (asciiTime[current]),
                 ".%06ld", (binaryTime.tv_nsec % 1000000000L) / 1000L) ;
    } else {
        strftime (asciiTime[current], 64, format, &calendarTime) ;
    }

    return (asciiTime[current]) ;

}

time_t tsConvertToMs (struct  timespec  time)
{
/* Local variables.  */
    time_t result ;
    
    result = 0;
     if (time.tv_sec != 0) {
        result += time.tv_sec / MILLIS_IN_ONE_SEC;
     }
     if (time.tv_nsec != 0) {
        result += time.tv_nsec / NANOS_IN_MILLIS;
     }

    return result ;

}


#endif

