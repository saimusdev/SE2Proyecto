#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <time.h>
#include <pthread.h>
#include <semaphore.h>

#include "calc.h"
#include "servers.h"


#define NUM_TASKS 3

// TASK 1
#define T1_PRIORITY 5 // 0..31
#define T1_COMP_TIME 10
#define T1_PERIOD 100
void task1(void);
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

struct thread_arg {
    int data1, data2;
};

void set_thread_attributes(pthread_attr_t *attributes, int priority, int scheduling_algorithm);

int main(void)
{
    int i;

    /* Pointers of tasks to be executed by each thread */
    void (*tasks[]) (void) = { task1, task2, task3 };

    static const unsigned char tasks_priority[] = { T1_PRIORITY, T2_PRIORITY, T3_PRIORITY };
    
    pthread_t threads[NUM_TASKS];
    pthread_attr_t thread_attributes[NUM_TASKS];
    struct thread_arg thread_args[NUM_TASKS];
    
    /* For each of the threads, set its attributes */ 
    for (i = 0; i < NUM_TASKS; i++)
    {
        set_thread_attributes(&thread_attributes[i], tasks_priority[i], SCHED_FIFO);
    }

    /* Create the servers, which the tasks make use of */
    create_servers();

    /* Create independent threads: one for each task */
    for (i = 0; i < NUM_TASKS; i++)
    {
        if (pthread_create(&threads[i], &thread_attributes[i], (void *)tasks[i], &thread_args[i]) != 0) {
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

/*
 *  ======== task1 ========
 */
void task1(void)
{
    printf("Executing task1\n");
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

/*
 *  ======== task3 ========
 */
void task4(void)
{
    printf("Executing task4\n");
}


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

void task2(void)
{

    UInt32 next, period = T2_PERIOD ;
    int d ;

    next = Clock_getTicks();

    for (;;) {

        CS (T2_COMP_TIME) ;
        S21 () ;

        next += period ;
        d = next - Clock_getTicks() ;
        if (d < 0) d = 0 ;
        Task_sleep(d);
    }
}

void task3(void)
{

    UInt32 next, period = T3_PERIOD ;
    int d ;

    next = Clock_getTicks();

    for (;;) {

        S22 () ;
    	CS (T3_COMP_TIME) ;
    	S12 () ;

        next += period ;
        d = next - Clock_getTicks() ;
        if (d < 0) d = 0 ;
        Task_sleep(d);
    }
}

*/
