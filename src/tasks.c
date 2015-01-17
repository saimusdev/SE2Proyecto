/*******************************************************************************

File: tasks.c

Author: Simon Ortego Parra

*******************************************************************************/

#include <stdio.h>
#include <time.h>

#include "ts_util.h"
#include "delay.h"
#include "tasks.h"
#include "servers.h"

#define MILLIS_IN_ONE_SEC 1000
#define NANOS_IN_MILLIS 1000000

void periodic_task(void *task)
{
    int task_id;
    void (*task_body) (struct timespec);
    struct timespec next, comp_time, period;
    
    task_id = ((task_parameters *) task) -> task_id;
    task_body = ((task_parameters *) task) -> task_body;

    /* Fills the TIMESPEC struct from the computation time given in milliseconds */ 
    comp_time.tv_sec = ((task_parameters *) task) -> computation_time / MILLIS_IN_ONE_SEC;
    comp_time.tv_nsec = (((task_parameters *) task) -> computation_time % MILLIS_IN_ONE_SEC) * NANOS_IN_MILLIS;

    /* Fills the TIMESPEC struct from the period value given in milliseconds */ 
    period.tv_sec = ((task_parameters *) task) -> period / MILLIS_IN_ONE_SEC;
    period.tv_nsec = (((task_parameters *) task) -> period % MILLIS_IN_ONE_SEC) * NANOS_IN_MILLIS;

    printf("task#%d: started...\n", task_id);

    if (clock_gettime (CLOCK_MONOTONIC, &next) != 0) {
        fprintf(stderr, "task#%d: periodic_task(): failed to get the current time", task_id);
        perror(NULL);
        return;
    }

    for (;;) {
        task_body(comp_time);
        next = tsAdd(next, period) ;
        clock_nanosleep (CLOCK_MONOTONIC, TIMER_ABSTIME, &next, 0) ;
    }


}

void t1_task_body(struct timespec comp_time)
{
    delay_ms(comp_time); /* doing stuff */ 
    server1_func_1();
}

void t2_task_body(struct timespec comp_time)
{
    delay_ms(comp_time); /* doing stuff */ 
    server2_func_1();
}

void t3_task_body(struct timespec comp_time)
{
    server2_func_2();
    delay_ms(comp_time); /* doing stuff */ 
    server1_func_2();
}

