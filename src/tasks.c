/*******************************************************************************

File: tasks.c

Author: Simon Ortego Parra

*******************************************************************************/

#include <stdio.h>
#include <time.h>
#include <pthread.h>

#include "ts_util.h"
#include "calc.h"
#include "tasks.h"
#include "servers.h"

int max_sched_priority;
pthread_t running_threads[NUM_TASKS];

void set_threads_sched (pthread_attr_t *thread_attr, int priority, int sched_alg);

void add_task_event (int event_id, events_history *history);

void periodic_task(void *task)
{
    int task_id;
    void (*task_body) (struct timespec, events_history *);
    events_history *history;
    struct timespec next, comp_time, period;
    
    task_id = ((task_params *) task) -> task_id;
    task_body = ((task_params *) task) -> task_body;
    history = ((task_params *) task) -> history;

    /* Fills the TIMESPEC struct from the computation time given in milliseconds */ 
    comp_time.tv_sec = ((task_params *) task) -> computation_time / MILLIS_IN_ONE_SEC;
    comp_time.tv_nsec = (((task_params *) task) -> computation_time % MILLIS_IN_ONE_SEC) * NANOS_IN_MILLIS;

    /* Fills the TIMESPEC struct from the period value given in milliseconds */ 
    period.tv_sec = ((task_params *) task) -> period / MILLIS_IN_ONE_SEC;
    period.tv_nsec = (((task_params *) task) -> period % MILLIS_IN_ONE_SEC) * NANOS_IN_MILLIS;

#ifdef VERBOSE
    printf("T%d: started\n", task_id);
#endif

    if (clock_gettime (CLOCK_MONOTONIC, &next)) {
        fprintf(stderr, "T%d: periodic_task(): failed to get the current time: ", task_id);
        perror(NULL);
        return;
    }
    add_task_event(BIRTH, history);

    // for (;;) {
    int i;
    for (i = 0; i < NUM_TASK_ITERATIONS; i++) {
#ifdef VERBOSE
    printf("T%d: activated\n", task_id);
#endif
        switch(i) {
            case 0:
                add_task_event(T1_EXECUTING, history);
                break;
            case 1:
                add_task_event(T2_EXECUTING, history);
                break;
            case 2:
                add_task_event(T3_EXECUTING, history);
        }
        task_body(comp_time,history);
        add_task_event(COMPLETION, history);
        next = tsAdd(next, period);
        clock_nanosleep (CLOCK_MONOTONIC, TIMER_ABSTIME, &next, 0);
        add_task_event(ACTIVATION, history);
    }

    add_task_event(DEATH, history);
    pthread_exit(task);
}

void t1_task_body(struct timespec comp_time, events_history *history)
{
    calc(comp_time); /* doing stuff */ 
    server1_func_1(1,history);
}

void t2_task_body(struct timespec comp_time, events_history *history)
{
    calc(comp_time); /* doing stuff */ 
    server2_func_1(2,history);
}

void t3_task_body(struct timespec comp_time, events_history *history)
{
    server2_func_2(3,history);
    calc(comp_time); /* doing stuff */ 
    server1_func_2(3,history);
}

void create_tasks (pthread_t *threads, pthread_attr_t *thread_attr, task_params *params) 
{
#ifdef FIFO_SCHEDULING
    max_sched_priority = MAX_SCHED_FIFO_PRIORITY;
#endif
#ifdef ROUND_ROBIN_SCHEDULING
    max_sched_priority = MAX_SCHED_RR_PRIORITY;
#endif

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
        params[i].task_id = i+1;
        params[i].period = tasks_period[i];
        params[i].computation_time = tasks_comp_time[i];
        params[i].task_body = tasks_body[i];
        params[i].history = create_events_history(i+1);
        running_threads[i] = threads[i];
#ifdef FIFO_SCHEDULING
        set_threads_sched(&thread_attr[i], tasks_priority[i], SCHED_FIFO);
#endif
#ifdef ROUND_ROBIN_SCHEDULING
        set_threads_sched(&thread_attr[i], tasks_priority[i], SCHED_RR);
#endif
#ifdef VERBOSE
        printf("T%d: params set\n", i+1);
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

void add_task_event (int event_id, events_history *history)
{
    /*
    int thread_priority;
    pthread_attr_t thread_attr;
    struct sched_param thread_sched;

    // Retrieve the thread attributes and with those, the scheduling parameters: thread priority 
    if (pthread_getattr_np(pthread_self(), &thread_attr)) {
        fprintf(stderr, "add_task_event(): failed to get the running thread attributes: ");
        perror(NULL);
        return;
    } else if (pthread_attr_getschedparam(&thread_attr, &thread_sched)) {
        fprintf(stderr, "add_task_event(): failed to get the running thread scheduling parameters (priority): ");
        perror(NULL);
        return;
    } 
    // Save the current thread's priority 
    thread_priority = thread_sched.sched_priority;

    // Set the thread's priority to the max level 
    if (pthread_setschedprio(pthread_self(), max_sched_priority)) {
        fprintf(stderr, "add_task_event(): failed to elevate the thread's priority: ");
        perror(NULL);
        return;
    }

    // Add the event, without being preempted 
    add_event(event_id, history);

    // Restore the original thread priority 
    if (pthread_setschedprio(pthread_self(), thread_priority)) {
        fprintf(stderr, "add_task_event(): failed to restore the thread's priority: ");
        perror(NULL);
        return;
    }
    */
    add_event(event_id, history);
}

