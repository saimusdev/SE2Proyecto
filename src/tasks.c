/*******************************************************************************

File: tasks.c

Author: Simon Ortego Parra

*******************************************************************************/

#include <stdio.h>
#include <time.h>
#include <pthread.h>

#include "ts_util.h"
#include "delay.h"
#include "tasks.h"
#include "servers.h"

void set_threads_sched (pthread_attr_t *thread_attr, int priority, int sched_alg);

void periodic_task(void *task)
{
    int task_id;
    void (*task_body) (struct timespec);
    struct timespec next, comp_time, period;
    
    task_id = ((task_params *) task) -> task_id;
    task_body = ((task_params *) task) -> task_body;

    /* Fills the TIMESPEC struct from the computation time given in milliseconds */ 
    comp_time.tv_sec = ((task_params *) task) -> computation_time / MILLIS_IN_ONE_SEC;
    comp_time.tv_nsec = (((task_params *) task) -> computation_time % MILLIS_IN_ONE_SEC) * NANOS_IN_MILLIS;

    /* Fills the TIMESPEC struct from the period value given in milliseconds */ 
    period.tv_sec = ((task_params *) task) -> period / MILLIS_IN_ONE_SEC;
    period.tv_nsec = (((task_params *) task) -> period % MILLIS_IN_ONE_SEC) * NANOS_IN_MILLIS;

    printf("task #%d: started\n", task_id);

    if (clock_gettime (CLOCK_MONOTONIC, &next) != 0) {
        fprintf(stderr, "task #%d: periodic_task(): failed to get the current time", task_id);
        perror(NULL);
        return;
    }

    // for (;;) {
    int i, num_iter;
    for (i = 0, num_iter = 5; i < num_iter; i++) {
        task_body(comp_time);
        next = tsAdd(next, period) ;
        clock_nanosleep (CLOCK_MONOTONIC, TIMER_ABSTIME, &next, 0) ;
    }


}

void t1_task_body(struct timespec comp_time)
{
    delay_ms(comp_time); /* doing stuff */ 
    server1_func_1(1);
}

void t2_task_body(struct timespec comp_time)
{
    delay_ms(comp_time); /* doing stuff */ 
    server2_func_1(2);
}

void t3_task_body(struct timespec comp_time)
{
    server2_func_2(3);
    delay_ms(comp_time); /* doing stuff */ 
    server1_func_2(3);
}

void create_tasks (pthread_attr_t *thread_attr, task_params *params) 
{
    /* Priorities of each of the tasks */
    static unsigned char tasks_priority[NUM_TASKS];
    tasks_priority[0] = T1_PRIORITY;
    tasks_priority[1] = T2_PRIORITY;
    tasks_priority[2] = T3_PRIORITY;

    /* Periods of each of the tasks */
    static unsigned int tasks_period[NUM_TASKS];
    tasks_period[0] = T1_PERIOD;
    tasks_period[1] = T2_PERIOD;
    tasks_period[2] = T3_PERIOD;

    /* Computation time of each of the tasks */
    static unsigned int tasks_comp_time[NUM_TASKS];
    tasks_comp_time[0] = T1_COMP_TIME;
    tasks_comp_time[1] = T2_COMP_TIME;
    tasks_comp_time[2] = T3_COMP_TIME;

    /* Task code executed by each periodic task and,
     * consequently, by each thread */
    static void *tasks_body[NUM_TASKS];
    tasks_body[0] = t1_task_body;
    tasks_body[1] = t2_task_body;
    tasks_body[2] = t3_task_body;
    
    /* For each of the threads, set its attributes and parameters */ 
    int i;
    for (i = 0; i < NUM_TASKS; i++) {
        params[i].task_id = i;
        params[i].period = tasks_period[i];
        params[i].computation_time = tasks_comp_time[i];
        params[i].task_body = tasks_body[i];
        set_threads_sched(&thread_attr[i], tasks_priority[i], SCHED_FIFO);
#ifdef DEBUG
        printf("task#%d: params set\n", i+1);
#endif
    }
}

void set_threads_sched (pthread_attr_t *thread_attr, int priority, int sched_alg)
{
    struct sched_param thread_sched;

    /* Initialize threads attributes with default values */
    pthread_attr_init(thread_attr);

    /* Define threads scheduling inheritance mode: not inherited, aka explicit */ 
    pthread_attr_setinheritsched(thread_attr, PTHREAD_EXPLICIT_SCHED);

    /* Define threads scheduling policy: FIFO */ 
    pthread_attr_setschedpolicy(thread_attr, sched_alg);

    /* Define threads fixed priority */ 
    thread_sched.sched_priority = priority;

    /* Set threads scheduling parameters */
    pthread_attr_setschedparam(thread_attr, &thread_sched);

}

