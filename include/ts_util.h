/*******************************************************************************

File: ts_util.h

Author: Alex Measday
        Simon Ortego Parra
        
*******************************************************************************/

#ifndef  TS_UTIL_H
#define  TS_UTIL_H

#define MILLIS_IN_ONE_SEC 1000
#define NANOS_IN_MILLIS 1000000

extern  struct  timespec tsAdd (struct timespec time1, struct timespec time2);

extern  int  tsCompare (struct timespec time1, struct timespec time2);

#endif /* TS_UTIL_H */
