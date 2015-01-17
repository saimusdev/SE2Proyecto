/*******************************************************************************

File: tasks.h

Author: Simon Ortego Parra

*******************************************************************************/

#ifndef _TASKS_H
#define _TASKS_H


void periodic_task(void *parameters);

typedef struct task_parameters {
    int task_id, 
    	period,	
		computation_time;
    void (*task_body) (struct timespec);
} task_parameters;


#define NUM_TASKS 3

/*
#define T1_PRIORITY 5
#define T1_COMP_TIME 10
#define T1_PERIOD 100
void t1_task_body(struct timespec comp_time);

#define T2_PRIORITY 3
#define T2_COMP_TIME 60
#define T2_PERIOD 200
void t2_task_body(struct timespec comp_time);

TASK 3 
#define T3_PRIORITY 1
#define T3_COMP_TIME 30
#define T3_PERIOD 400
void t3_task_body(struct timespec comp_time);
*/


/* TASK 1 */
#define T1_PRIORITY 5
#define T1_COMP_TIME 250
#define T1_PERIOD 1000
void t1_task_body(struct timespec comp_time);

/* TASK 2 */
#define T2_PRIORITY 3
#define T2_COMP_TIME 600
#define T2_PERIOD 2000
void t2_task_body(struct timespec comp_time);

/* TASK 3 */
#define T3_PRIORITY 1
#define T3_COMP_TIME 350
#define T3_PERIOD 4000
void t3_task_body(struct timespec comp_time);

/* ... */

#endif /* _TASKS_H */
