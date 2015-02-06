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

#ifdef DEBUG
        printf("S11 params set\n");
#endif
    /* server 1 - function 2 */
    s12_comp_time.tv_sec = S12_COMP_TIME / MILLIS_IN_ONE_SEC;
    s12_comp_time.tv_nsec = (S12_COMP_TIME % MILLIS_IN_ONE_SEC) * NANOS_IN_MILLIS;
    pthread_mutex_init(&s1_mutex, NULL);

#ifdef DEBUG
        printf("S12 params set\n");
#endif
	/* server 2 - function 1 */
    s21_comp_time.tv_sec = S21_COMP_TIME / MILLIS_IN_ONE_SEC;
    s21_comp_time.tv_nsec = (S21_COMP_TIME % MILLIS_IN_ONE_SEC) * NANOS_IN_MILLIS;

#ifdef DEBUG
        printf("S21 params set\n");
#endif
    /* server 2 - function 2 */
    s22_comp_time.tv_sec = S21_COMP_TIME / MILLIS_IN_ONE_SEC;
    s22_comp_time.tv_nsec = (S21_COMP_TIME % MILLIS_IN_ONE_SEC) * NANOS_IN_MILLIS;
	pthread_mutex_init(&s2_mutex, NULL);
#ifdef DEBUG
        printf("S22 params set\n");
#endif
}

void server_function (int server_id, int function_id, 
		struct timespec computation_time, pthread_mutex_t mutex, int task_id, events_history *history) 
{
#ifdef DEBUG
	printf("T%d @ S%d%d: enters\n", server_id, function_id, task_id);
#endif
	
	/* tries to aquire mutex */
#ifdef DEBUG
	printf("T%d @ S%d%d: tries to aquire mutex\n", server_id, function_id, task_id);
#endif	
	pthread_mutex_lock(&mutex);

	/* --- Critical Section ----- */
	add_task_event(CS_ENTRY, history);
#ifdef DEBUG
	printf("T%d @ S%d%d: aquires mutex. enters cs\n", server_id, function_id, task_id);
#endif
	calc(computation_time);
	add_task_event(CS_EXIT, history);
#ifdef DEBUG
	printf("T%d @ S%d%d: exits cs\n", server_id, function_id, task_id);
#endif
	/* ------------------------- */

	/* releases mutex */
#ifdef DEBUG
	printf("T%d @ S%d%d: releases mutex\n", server_id, function_id, task_id);
#endif
	pthread_mutex_unlock(&mutex);	
}

void server1_func_1 (int task_id, events_history *history) 
{	
	server_function (1, 1, s11_comp_time, s1_mutex, task_id, history);
}

void server1_func_2 (int task_id, events_history *history) 
{	
	server_function (1, 2, s12_comp_time, s1_mutex, task_id, history);
}

void server2_func_1 (int task_id, events_history *history) 
{	
	server_function (2, 1, s21_comp_time, s2_mutex, task_id, history);
}

void server2_func_2 (int task_id, events_history *history) 
{	
	server_function (2, 2, s22_comp_time, s2_mutex, task_id, history);
}
