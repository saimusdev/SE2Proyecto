/*******************************************************************************

File: main.c

Author: Simon Ortego Parra

*******************************************************************************/

 #include <stdio.h>
#include <string.h>
#include <errno.h>

#include <time.h>
#include <pthread.h>
#include <semaphore.h>

#include "servers.h"
#include "tasks.h"


void set_thread_attributes(pthread_attr_t *attributes, int priority, int scheduling_algorithm);

int main(void)
{
    int i;

    /* Data needed for the execution of each periodic task (id, period, comp_time, task executed) */
    task_parameters thread_params[NUM_TASKS];

    /* Priorities of each of the tasks */
    static unsigned char tasks_priority[NUM_TASKS];
    tasks_priority[0] = T1_PRIORITY;
    tasks_priority[1] = T2_PRIORITY;
    tasks_priority[2] = T3_PRIORITY;
    //...

    /* Periods of each of the tasks */
    static unsigned int tasks_period[NUM_TASKS];
    tasks_period[0] = T1_PERIOD;
    tasks_period[1] = T2_PERIOD;
    tasks_period[2] = T3_PERIOD;
    //...

    /* Computation time of each of the tasks */
    static unsigned int tasks_comp_time[NUM_TASKS];
    tasks_comp_time[0] = T1_COMP_TIME;
    tasks_comp_time[1] = T2_COMP_TIME;
    tasks_comp_time[2] = T3_COMP_TIME;
    //...

    /* Task code executed by each periodic task and consequently, each thread */
    static void *tasks_body[NUM_TASKS];
    tasks_body[0] = t1_task_body;
    tasks_body[1] = t2_task_body;
    tasks_body[2] = t3_task_body;
    //...
    
    /* Threads that execute tasks and its parameters */
    pthread_t threads[NUM_TASKS];
    pthread_attr_t thread_attributes[NUM_TASKS];
    
    /* For each of the threads, set its attributes and parameters */ 
    for (i = 0; i < NUM_TASKS; i++)
    {
        thread_params[i].task_id = i;
        thread_params[i].period = tasks_period[i];
        thread_params[i].computation_time = tasks_comp_time[i];
        thread_params[i].task_body = tasks_body[i];
        set_thread_attributes(&thread_attributes[i], tasks_priority[i], SCHED_FIFO);
    }

    /* Create the servers, which the tasks make use of */
    create_servers();

    /* Create independent threads: one for each task */
    for (i = 0; i < NUM_TASKS; i++)
    {
        if (pthread_create(&threads[i], &thread_attributes[i], (void *)periodic_task, &thread_params[i]) != 0) {
            perror("pthread_create(): failed to create thread #1");
            return -1;
        }
    }

    /** 
     * Dead code (supposedly): Wait for threads to finish. 
     * Actually, Main thread sleeps forever */
    for (i = 0; i < NUM_TASKS; i++)
    {
        if (pthread_join(threads[i], NULL) != 0) {
            fprintf(stderr, "Thread %d did not terminate normally", i);
            perror(NULL);
        }
    }

    return 0;
}

void set_thread_attributes(pthread_attr_t *attributes, int priority, int scheduling_algorithm)
{

    struct sched_param thread_param;

    /* Initialize threads attributes with default values */
    pthread_attr_init(attributes);

    /* Define threads scheduling inheritance mode: not inherited, aka explicit */ 
    pthread_attr_setinheritsched(attributes, PTHREAD_EXPLICIT_SCHED);

    /* Define threads scheduling policy: FIFO */ 
    pthread_attr_setschedpolicy(attributes, scheduling_algorithm);

    /* Define threads fixed priority */ 
    thread_param.sched_priority = priority;

    /* Set threads scheduling parameters */
    pthread_attr_setschedparam(attributes, &thread_param);

}

