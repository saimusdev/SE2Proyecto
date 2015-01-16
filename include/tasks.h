/*
 * tasks.h
 */

#ifndef _TASKS_H
#define _TASKS_H

#define NUM_TASKS 3

// TASK 1
#define T1_PRIORITY 5 // 0..31
#define T1_COMP_TIME 10
#define T1_PERIOD 100
//void task1(void);
void task1(void *data);
/*************************/

// TASK 2
#define T2_PRIORITY 3
#define T2_COMP_TIME 60
#define T2_PERIOD 200
void task2(void);
/*************************/

/* TASK 3 */
#define T3_PRIORITY 1
#define T3_COMP_TIME 30
#define T3_PERIOD 400
void task3(void);
/*************************/

struct task_params {
    int one, two;
};

#endif /* _TASKS_H */
