/*******************************************************************************

File: main.c

Author: Simon Ortego Parra

*******************************************************************************/
#include <stdio.h>
#include <pthread.h>

#include "tasks.h"
#include "servers.h"


int main (int argc, char **argv)
{
    /* Threads that execute tasks and its attributes */
    pthread_t threads[NUM_TASKS];
    pthread_attr_t thread_attributes[NUM_TASKS];

    /* Timespec structure to set the timer to zero at 
     * the beginning of the program execution */
    struct timespec start;

    /* Data needed for the execution of each periodic task:
     * id, period, computation time & task code executed */
    task_params params[NUM_TASKS];
    
#ifdef VERBOSE
        printf("create tasks\n");
#endif
    /* Set the parameters for the tasks (including thread attributes) */
    create_tasks(threads, thread_attributes, params);

#ifdef VERBOSE
    printf("create servers\n");
#endif
    /* Create the servers, which the tasks make use of */
    create_servers();

    /* Initialize clock */
    start.tv_sec = 0;
    start.tv_nsec = 0;
    if (clock_settime(CLOCK_REALTIME, &start)) {
        fprintf(stderr, "main(): failed to reset the timer: ");
        perror(NULL);
        return -1;
    }

    //printf("All time output is given in milliseconds.\n\n");
    //printf("\nTask  Pr.   C    T     D\n");
    //printf("---------------------------\n");
    //printf("T1    %d   %d   %d   %d\n", T1_PRIORITY, T1_COMP_TIME, T1_PERIOD, T1_PERIOD);
    //printf("T2    %d   %d   %d   %d\n", T2_PRIORITY, T2_COMP_TIME, T2_PERIOD, T2_PERIOD);
    //printf("T3    %d   %d   %d   %d\n\n", T3_PRIORITY, T3_COMP_TIME, T3_PERIOD, T3_PERIOD);

#ifdef VERBOSE
        printf("starting threads..");
#endif
    int i;
    /* Create one independent thread for each task */
    for (i = 0; i < NUM_TASKS; i++) {
        if (pthread_create(&threads[i], &thread_attributes[i], (void *)periodic_task, &params[i])) {
            fprintf(stderr, "pthread_create(): failed to create thread#%d: ", i);
            perror(NULL);
            return -1;
        }
    }

    /* Dead code (supposedly, if tasks run forever) */
    for (i = 0; i < NUM_TASKS; i++) {
        if (pthread_join(threads[i], NULL)) {
            fprintf(stderr, "pthread_join(): Thread %d did not terminate normally: ", i);
            perror(NULL);
            return -1;
        }
        print_events(*params[i].history);
        clear_history(params[i].history);
    }

    return 0;
}
