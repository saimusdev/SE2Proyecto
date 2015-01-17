/*******************************************************************************

File: ts_util.c

Author: Alex Measday

*******************************************************************************

Copyright (c) 2009  Alex Measday

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

********************************************************************************/

#include  <time.h>           /* Time definitions. */ 


/*!*****************************************************************************

Procedure:

    tsAdd ()


Purpose:

    Function tsAdd() returns the sum of two TIMESPECs.


    Invocation:

        result = tsAdd (time1, time2) ;

    where

        <time1>     - I
            is the first operand, a time represented by a POSIX TIMESPEC
            structure.
        <time2>     - I
            is the second operand, a time represented by a POSIX TIMESPEC
            structure.
        <result>    - O
            returns, in a POSIX TIMESPEC structure, the sum of TIME1 and
            TIME2.

*******************************************************************************/


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

/*!*****************************************************************************

Procedure:

    tsCompare ()


Purpose:

    Function tsCompare() compares two TIMESPECs.


    Invocation:

        comparison = tsCompare (time1, time2) ;

    where

        <time1>     - I
            is a time represented by a POSIX TIMESPEC structure.
        <time2>     - I
            is another time represented by a POSIX TIMESPEC structure.
        <comparison>    - O
            returns an integer indicating how the times compare:
                    -1  if TIME1 < TIME2
                     0  if TIME1 = TIME2
                    +1  if TIME1 > TIME2

*******************************************************************************/


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

