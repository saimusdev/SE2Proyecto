/*******************************************************************************

File: ts_util.h

Author: Alex Measday
        Simon Ortego Parra
        
*******************************************************************************/

#ifndef  TS_UTIL_H
#define  TS_UTIL_H
  
#define MILLIS_IN_ONE_SEC 1000L
#define NANOS_IN_MILLIS 1000000L

struct timespec tsAdd (struct timespec time1, struct timespec time2);

int tsCompare (struct timespec time1, struct timespec time2);

time_t tsConvertToMs (struct timespec time);

#endif /* TS_UTIL_H */
