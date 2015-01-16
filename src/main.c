#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <time.h>
#include <pthread.h>
#include <semaphore.h>

#include "calc.h"
#include "servers.h"
#include "tasks.h"

void set_thread_attributes(pthread_attr_t *attributes, int priority, int scheduling_algorithm);

int main(void)
{
    int i;

    /* Pointers of tasks to be executed by each thread */
    //void (*tasks[]) (void) = { task1, task2, task3 };
    void (*tasks[]) (void *) = { task1, task1, task1 };

    static const unsigned char tasks_priority[] = { T1_PRIORITY, T2_PRIORITY, T3_PRIORITY };
    
    pthread_t threads[NUM_TASKS];
    pthread_attr_t thread_attributes[NUM_TASKS];
    struct task_params thread_args[NUM_TASKS];
    
    /* For each of the threads, set its attributes */ 
    for (i = 0; i < NUM_TASKS; i++)
    {
        thread_args[i].one = i+1;
        thread_args[i].two = 2*(i+1);
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

