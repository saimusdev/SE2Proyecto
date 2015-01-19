/*******************************************************************************

File: servers.c

Author: Simon Ortego Parra

*******************************************************************************/

#include <stdio.h>
#include <time.h>
#include <pthread.h>

#include "ts_util.h"
#include "delay.h"
#include "servers.h"

static struct timespec s11_comp_time, s12_comp_time,
					   s21_comp_time, s22_comp_time;

pthread_mutex_t s11_mutex, s12_mutex,
				s21_mutex, s22_mutex;

void create_servers (void) 
{	
	/* server 1 - function 1 */
	s11_comp_time.tv_sec = S11_COMP_TIME / MILLIS_IN_ONE_SEC;
    s11_comp_time.tv_nsec = (S11_COMP_TIME % MILLIS_IN_ONE_SEC) * NANOS_IN_MILLIS;
    pthread_mutex_init(&s11_mutex, NULL);

#ifdef DEBUG
        printf("server#1: f1 params set\n");
#endif
    /* server 1 - function 2 */
    s12_comp_time.tv_sec = S12_COMP_TIME / MILLIS_IN_ONE_SEC;
    s12_comp_time.tv_nsec = (S12_COMP_TIME % MILLIS_IN_ONE_SEC) * NANOS_IN_MILLIS;
	pthread_mutex_init(&s11_mutex, NULL);

#ifdef DEBUG
        printf("server#1: f2 params set\n");
#endif
	/* server 2 - function 1 */
    s21_comp_time.tv_sec = S21_COMP_TIME / MILLIS_IN_ONE_SEC;
    s21_comp_time.tv_nsec = (S21_COMP_TIME % MILLIS_IN_ONE_SEC) * NANOS_IN_MILLIS;
    pthread_mutex_init(&s11_mutex, NULL);

#ifdef DEBUG
        printf("server#2: f1 params set\n");
#endif
    /* server 2 - function 2 */
    s22_comp_time.tv_sec = S21_COMP_TIME / MILLIS_IN_ONE_SEC;
    s22_comp_time.tv_nsec = (S21_COMP_TIME % MILLIS_IN_ONE_SEC) * NANOS_IN_MILLIS;
	pthread_mutex_init(&s11_mutex, NULL);
#ifdef DEBUG
        printf("server#2: f2 params set\n");
#endif
}

void server1_func_1 (unsigned char task_id) 
{	
#ifdef DEBUG
	printf("task #%d: S11\n", task_id);
#endif

	pthread_mutex_lock(&s11_mutex);
	/* --- CS ----- */
	delay_ms(s11_comp_time);
	/* ------------ */
	pthread_mutex_unlock(&s11_mutex);
}

void server1_func_2 (unsigned char task_id) 
{
#ifdef DEBUG
	printf("task #%d: S12\n", task_id);
#endif

	pthread_mutex_lock(&s11_mutex);
	/* --- CS ----- */
	delay_ms(s12_comp_time);
	/* ------------ */
	pthread_mutex_unlock(&s11_mutex);
}

void server2_func_1 (unsigned char task_id) 
{
#ifdef DEBUG
	printf("task #%d: S21\n", task_id);
#endif

	pthread_mutex_lock(&s21_mutex);
	/* --- CS ----- */
	delay_ms(s21_comp_time);
	/* ------------ */
	pthread_mutex_unlock(&s21_mutex);
}

void server2_func_2 (unsigned char task_id) 
{
#ifdef DEBUG
	printf("task #%d: S22\n", task_id);
#endif

	pthread_mutex_lock(&s22_mutex);
	/* --- CS ----- */
	delay_ms(s22_comp_time);
	/* ------------ */
	pthread_mutex_unlock(&s22_mutex);
}

