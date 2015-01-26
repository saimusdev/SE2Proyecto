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
 	events_history *history;
    void (*task_body) (struct timespec, events_history *);
} task_params;

void periodic_task(void *parameters);

void create_tasks (pthread_attr_t *thread_attr, task_params *params);

#define NUM_TASKS 3
#define NUM_TASK_ITERATIONS 2

/* Task 1
#define T1_PRIORITY 5
#define T1_COMP_TIME 10
#define T1_PERIOD 100  */
#define T1_PRIORITY 5
#define T1_COMP_TIME 100
#define T1_PERIOD 1000
void t1_task_body(struct timespec comp_time, events_history *history);

/* Task 1
#define T2_PRIORITY 3
#define T2_COMP_TIME 60
#define T2_PERIOD 200  */
#define T2_PRIORITY 3
#define T2_COMP_TIME 600
#define T2_PERIOD 2000
void t2_task_body(struct timespec comp_time, events_history *history);

/* Task 1
#define T3_PRIORITY 1
#define T3_COMP_TIME 30
#define T3_PERIOD 400  */
#define T3_PRIORITY 1
#define T3_COMP_TIME 300
#define T3_PERIOD 4000 
void t3_task_body(struct timespec comp_time, events_history *history);


#endif /* TASKS_H */
