/*******************************************************************************

File: tasks.h

Author: Simon Ortego Parra

*******************************************************************************/

#ifndef TASKS_H
#define TASKS_H

#include "events.h"

typedef struct task_params {
    int task_id, 
    	period,	
		computation_time;
	pthread_t *thread;
 	events_history *history;
    void (*task_body) (struct timespec, events_history *);
} task_params;

void periodic_task(void *parameters);

void create_tasks (pthread_t *threads, pthread_attr_t *thread_attr, task_params *params);

#define NUM_TASK_ITERATIONS 10

/*
SCHED_FIFO min/max priority     : 1/99
SCHED_RR min/max priority       : 1/99
SCHED_OTHER min/max priority    : 0/0
*/

#define FIFO_SCHEDULING YES
//#define ROUND_ROBIN_SCHEDULING YES
#define MIN_SCHED_FIFO_PRIORITY 1
#define MAX_SCHED_FIFO_PRIORITY 99
#define MIN_SCHED_RR_PRIORITY 1
#define MAX_SCHED_RR_PRIORITY 99

#define NUM_TASKS 3

/* TOOD: tal y como están los tiempos se ejecuta primero T1, cuando acaba 
   todas las iters. T2. Hay que hacer más largo el periodo */
/* Task 1 */
#define T1_PRIORITY 5
#define T1_COMP_TIME 10
#define T1_PERIOD 100
void t1_task_body(struct timespec comp_time, events_history *history);

/* Task 2 */
#define T2_PRIORITY 3
#define T2_COMP_TIME 50
#define T2_PERIOD 200
void t2_task_body(struct timespec comp_time, events_history *history);

/* Task 3 */
#define T3_PRIORITY 1
#define T3_COMP_TIME 30
#define T3_PERIOD 400 
void t3_task_body(struct timespec comp_time, events_history *history);


#endif /* TASKS_H */
