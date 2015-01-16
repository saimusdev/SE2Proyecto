#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <time.h>
#include <pthread.h>
#include <semaphore.h>

#include "computos.h"
#include "servidores.h"

/******************************************************************************/
/*                        Defines                                             */
/******************************************************************************/

// TASK 1
#define T1_PRIORITY 5 // 0..31
#define T1_COMP_TIME 10
#define T1_PERIOD 100

// TASK 2
#define T2_PRIORITY 3
#define T2_COMP_TIME 60
#define T2_PERIOD 200

// TASK 3
#define T3_PRIORITY 1
#define T3_COMP_TIME 30
#define T3_PERIOD 400

/******************************************************************************/
/*                        Global variables                                    */
/******************************************************************************/

struct thread_arg {
    int data1, data2;
};

void task1(void);
void task2(void);
void task3(void);


int set_thread_attributes(pthread_attr_t attributes, int priority, int scheduling_algorithm)
{
    struct sched_param thread_param;

    /* Initialize threads attributes with default values */
    pthread_attr_init(&attributes);

    /* Define threads scheduling inheritance mode: not inherited, aka explicit */ 
    if (pthread_attr_setinheritsched(&attributes, PTHREAD_EXPLICIT_SCHED) != 0) {
        fprintf(stderr,"Failed to set thread scheduling inheritance mode:");
        return -1;
    }

    /* Define threads scheduling policy: FIFO */ 
    if (pthread_attr_setschedpolicy(&attributes, scheduling_algorithm) != 0) {
        fprintf(stderr,"Failed to set thread scheduling policy:");
        return -1;
    }

    /* Define threads fixed priority */ 
    thread_param.sched_priority = priority;

    /* Set threads scheduling parameters */
    if (pthread_attr_setschedparam(&attributes, &thread_param) != 0) {
        fprintf(stderr,"Failed to set thread scheduling parameters:");
        return -1;
    }

    return 0;
}

int main(void)
{

    pthread_t thread1, thread2, thread3;
    pthread_attr_t thread1_attr, thread2_attr, thread3_attr;
    struct thread_arg thread1_arg, thread2_arg, thread3_arg;


    /* Set thread attributes */ 
    if (set_thread_attributes(thread1_attr, T1_PRIORITY, /*SCHED_FIFO*/-3) != 0) {
        char *error_str = strerror(errno);
        fprintf(stderr, error_str);
        return -1;
    }
    if (set_thread_attributes(thread2_attr, T2_PRIORITY, SCHED_FIFO) != 0) {
        fprintf(stderr, strerror(errno));
        return -1;
    }
    if (set_thread_attributes(thread3_attr, T3_PRIORITY, SCHED_FIFO) != 0) {
        fprintf(stderr, strerror(errno));
        return -1;
    }

    /* Create three independent threads: one for each task */
    if (pthread_create(&thread1, &thread1_attr, (void *)task1, &thread1_arg) != 0) {
        perror("Failed to create thread #1:");
        return -1;
    }
    if (pthread_create(&thread2, &thread2_attr, (void *)task2, &thread2_arg) != 0) {
        perror("Failed to create thread #2:");
        return -1;
    }
    if (pthread_create(&thread3, &thread3_attr, (void *)task3, &thread3_arg) != 0) {
        perror("Failed to create thread #3:");
        return -1;
    }

    Crear_Servidores ();

    /** 
     * Dead code (supposedly): 
     * Wait for threads to finish. 
     * Main thread sleeps forever */
    if (pthread_join(thread1, NULL) != 0) {
        perror("Thread #1 did not terminate normally: ");
        return -1;
    }
    if (pthread_join(thread2, NULL) != 0) {
        perror("Thread #1 did not terminate normally: ");
        return -1;
    }
    if (pthread_join(thread3, NULL) != 0) {
        perror("Thread #1 did not terminate normally: ");
        return -1;
    }

    return 0;
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
