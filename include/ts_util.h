/*******************************************************************************

File: ts_util.h

Author: Alex Measday
        Simon Ortego Parra
        
*******************************************************************************/

#ifndef  TS_UTIL_H
#define  TS_UTIL_H
  
#ifdef DEBUG     
#	include "pragmatics.h"
#endif

#define MILLIS_IN_ONE_SEC 1000L
#define NANOS_IN_MILLIS 1000000L

struct  timespec tsAdd (struct timespec time1, struct timespec time2);

int  tsCompare (struct timespec time1, struct timespec time2);

time_t tsConvertToMs (struct  timespec  time);

#ifdef DEBUG 
struct  timespec  tsSubtract (struct timespec time1, struct timespec time2);

const  char  *tsShow (struct timespec binaryTime, bool inLocal, const char *format);
#endif

#endif /* TS_UTIL_H */
