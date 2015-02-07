/*******************************************************************************

File: servers.c

Author: Simon Ortego Parra

*******************************************************************************/

#include <stdio.h>
#include <time.h>
#include <pthread.h>

#include "ts_util.h"
#include "events.h"
#include "calc.h"
#include "servers.h"

static struct timespec s11_comp_time, s12_comp_time,
					   s21_comp_time, s22_comp_time;

pthread_mutex_t s1_mutex, s2_mutex;

extern void add_task_event (int event_id, events_history *history);

void create_servers (void) 
{	
	/* server 1 - function 1 */
	s11_comp_time.tv_sec = S11_COMP_TIME / MILLIS_IN_ONE_SEC;
    s11_comp_time.tv_nsec = (S11_COMP_TIME % MILLIS_IN_ONE_SEC) * NANOS_IN_MILLIS;

    /* server 1 - function 2 */
    s12_comp_time.tv_sec = S12_COMP_TIME / MILLIS_IN_ONE_SEC;
    s12_comp_time.tv_nsec = (S12_COMP_TIME % MILLIS_IN_ONE_SEC) * NANOS_IN_MILLIS;

    pthread_mutex_init(&s1_mutex, NULL);

#ifdef VERBOSE
    printf("S1 params set\n");
#endif

	/* server 2 - function 1 */
    s21_comp_time.tv_sec = S21_COMP_TIME / MILLIS_IN_ONE_SEC;
    s21_comp_time.tv_nsec = (S21_COMP_TIME % MILLIS_IN_ONE_SEC) * NANOS_IN_MILLIS;

    /* server 2 - function 2 */
    s22_comp_time.tv_sec = S22_COMP_TIME / MILLIS_IN_ONE_SEC;
    s22_comp_time.tv_nsec = (S22_COMP_TIME % MILLIS_IN_ONE_SEC) * NANOS_IN_MILLIS;

	pthread_mutex_init(&s2_mutex, NULL);

#ifdef VERBOSE
    printf("S22 params set\n");
#endif
}

void server_function (struct timespec comp_time, pthread_mutex_t mutex, events_history *history) 
{
#ifdef VERBOSE
	printf("thread#%lu begins server function execution\n", (unsigned long int) pthread_self());
#endif
	
	/* tries to aquire mutex */
#ifdef VERBOSE
	printf("thread#%lu tries to aquire mutex\n", (unsigned long int) pthread_self());
#endif	
	pthread_mutex_lock(&mutex);

	/* --- Critical Section ----- */
	add_task_event(CS_ENTRY, history);
#ifdef VERBOSE
	printf("thread#%lu aquires mutex. enters cs\n", (unsigned long int) pthread_self());
#endif
	calc(comp_time);
	add_task_event(CS_EXIT, history);
#ifdef VERBOSE
	printf("thread#%lu exits cs\n", (unsigned long int) pthread_self());
#endif
	/* ------------------------- */

	/* releases mutex */
#ifdef VERBOSE
	printf("thread#%lu releases mutex\n", (unsigned long int) pthread_self());
#endif
	pthread_mutex_unlock(&mutex);	
}

void server1_func_1 (int task_id, events_history *history) 
{	
	server_function (s11_comp_time, s1_mutex, history);
}

void server1_func_2 (int task_id, events_history *history) 
{	
	server_function (s12_comp_time, s1_mutex, history);
}

void server2_func_1 (int task_id, events_history *history) 
{	
	server_function (s21_comp_time, s2_mutex, history);
}

void server2_func_2 (int task_id, events_history *history) 
{	
	server_function (s22_comp_time, s2_mutex, history);
}
