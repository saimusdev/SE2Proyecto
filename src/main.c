/*******************************************************************************

File: main.c

Author: Simon Ortego Parra

*******************************************************************************/
#include <stdio.h>
#include <pthread.h>

#include "tasks.h"
#include "servers.h"

int main (void)
{
    /* Threads that execute tasks and its attributes */
    pthread_t threads[NUM_TASKS];
    pthread_attr_t thread_attributes[NUM_TASKS];

    /* Data needed for the execution of each periodic task:
     * id, period, computation time & task code executed */
    task_params params[NUM_TASKS];

    
    /* Set the parameters for the tasks (including thread attributes) */
    create_tasks(thread_attributes, params);

    /* Create the servers, which the tasks make use of */
    create_servers();

    /* Create one independent thread for each task */
    int i;
    for (i = 0; i < NUM_TASKS; i++) {
        if (pthread_create(&threads[i], &thread_attributes[i], (void *)periodic_task, &params[i]) != 0) {
            fprintf(stderr, "pthread_create(): failed to create thread#%d", i);
            perror(NULL);
            return -1;
        }
    }

    /** 
     * Dead code (supposedly): Wait for threads to finish. 
     * Actually, Main thread sleeps forever */
    for (i = 0; i < NUM_TASKS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            fprintf(stderr, "pthread_join(): Thread %d did not terminate normally", i);
            perror(NULL);
            return -1;
        }
    }

    return 0;
}
