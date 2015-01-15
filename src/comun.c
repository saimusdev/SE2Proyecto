#include <stdio.h>
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

/*
 *  ======== main ========
 */
int main(void)
{

    pthread_t thread1, thread2, thread3;
    pthread_attr_t thread1_attr, thread2_attr, thread3_attr;
    struct sched_param thread1_fifo_param, thread2_fifo_param, thread3_fifo_param;
    struct thread_arg thread1_arg, thread2_arg, thread3_arg;

    /* Initialize threads attributes with default values */ 
    pthread_attr_init(&thread1_attr);
    pthread_attr_init(&thread2_attr);
    pthread_attr_init(&thread3_attr);

    /* Define threads scheduling inheritance mode: not inherited, aka explicit */ 
    if (pthread_attr_setinheritsched(&thread1_attr, PTHREAD_EXPLICIT_SCHED) != 0) {
        perror("Failed to set thread#1 scheduling inheritance mode:");
        return -1;
    }
    if (pthread_attr_setinheritsched(&thread2_attr, PTHREAD_EXPLICIT_SCHED) != 0) {
        perror("Failed to set thread#2 scheduling inheritance mode:");
        return -1;
    }
    if (pthread_attr_setinheritsched(&thread3_attr, PTHREAD_EXPLICIT_SCHED) != 0) {
        perror("Failed to set thread#3 scheduling inheritance mode:");
        return -1;
    }

    /* Define threads scheduling policy: FIFO */ 
    if (pthread_attr_setschedpolicy(&thread1_attr, SCHED_FIFO) != 0) {
        perror("Failed to set thread#1 scheduling policy:");
        return -1;
    }
    if (pthread_attr_setschedpolicy(&thread1_attr, SCHED_FIFO) != 0) {
        perror("Failed to set thread#2 scheduling policy:");
        return -1;
    }
    if (pthread_attr_setschedpolicy(&thread1_attr, SCHED_FIFO) != 0) {
        perror("Failed to set thread#3 scheduling policy:");
        return -1;
    }

    /* Define threads fixed priority */ 
    thread1_fifo_param.sched_priority = T1_PRIORITY;
    thread2_fifo_param.sched_priority = T2_PRIORITY;
    thread3_fifo_param.sched_priority = T3_PRIORITY;

    /* Set threads scheduling parameters */
    pthread_attr_setschedparam(&thread1_attr, &thread1_fifo_param);
    pthread_attr_setschedparam(&thread2_attr, &thread2_fifo_param);
    pthread_attr_setschedparam(&thread3_attr, &thread3_fifo_param);


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
    printf("Executing T1");
}


/*
 *  ======== task1 ========
 */
void task2(void)
{
    printf("Executing T2");
}


/*
 *  ======== task1 ========
 */
void task3(void)
{
    printf("Executing T3");
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
