/*
void task1(void)
{

    UInt32 next, period = T1_PERIOD ;
    int d ;

    next = Clock_getTicks();

    for (;;) {

        CS (T1_COMP_TIME) ;
        S11 () ;

        next += period ;
        d = next - Clock_getTicks() ;
        if (d < 0) d = 0 ;
        Task_sleep(d);
    }
}
*/

#include <stdio.h>

#include "tasks.h"

/*
 *  ======== task1 ========
 */
void task1(void *data)
{
    printf("Executing task1\n");
    printf("My data1: %d\n", ((struct task_params *) data) -> one);
    printf("My data1: %d\n", ((struct task_params *) data) -> two);
}


/*
 *  ======== task2 ========
 */
void task2(void)
{
    printf("Executing task2\n");
}


/*
 *  ======== task3 ========
 */
void task3(void)
{
    printf("Executing task3\n");
}
