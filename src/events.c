/******************************************************************************* 
File: events.h

Author: Simon Ortego Parra

*******************************************************************************/

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <pthread.h>

#include "events.h"
#include "tasks.h"
#include "servers.h"
#include "ts_util.h"

extern int max_sched_priority;

events_history *create_events_history (int task_id)
{
	events_history *new_history;
	new_history = malloc(sizeof(events_history));
	if (new_history != NULL) {
		new_history->task_id = task_id;
		new_history->first_event = NULL;
		new_history->last_event = NULL;
	}
	return new_history;
}

void clear_history (events_history *history)
{
	event *current, *next;
	for(current = history->first_event; current != NULL; current = next) {
		next = current->next_event;
		free(current);
	}
	free(history);
}

void add_event (unsigned char type, unsigned char server_id, events_history *history)
{
    int thread_priority;
    pthread_attr_t thread_attr;
    struct sched_param thread_sched;
    struct timespec timestamp;
	event *new_event;

    // Retrieve the thread attributes and with those, the scheduling parameters: thread priority 
    if (pthread_getattr_np(pthread_self(), &thread_attr)) {
        fprintf(stderr, "add_event(): failed to get the running thread attributes: ");
        perror(NULL);
        return;
    } else if (pthread_attr_getschedparam(&thread_attr, &thread_sched)) {
        fprintf(stderr, "add_event(): failed to get the running thread scheduling parameters (priority): ");
        perror(NULL);
        return;
    } 

    // Save the current thread's priority 
    thread_priority = thread_sched.sched_priority;

    // Set the thread's priority to the max level 
    if (pthread_setschedprio(pthread_self(), max_sched_priority)) {
        fprintf(stderr, "add_event(): failed to elevate the thread's priority: ");
        perror(NULL);
        return;
    }

   	clock_gettime(CLOCK_REALTIME, &timestamp);   
	new_event = malloc(sizeof(event));

	if (new_event != NULL) {
		/* if could allocate memory for the new event */
		new_event->type = type;
		new_event->server_id = server_id;
		new_event->timestamp.tv_sec = timestamp.tv_sec;
		new_event->timestamp.tv_nsec = timestamp.tv_nsec;
		new_event->next_event = NULL;

		if (history->last_event != NULL) {
			/* if history is not empty */
			history->last_event->next_event = new_event;	
		} else {
			/* if history is empty */
			history->first_event = new_event;
		}
		history->last_event = new_event;
	} else {
        fprintf(stderr, "add_event(): could not allocate memory for new event: ");
	}

    // Restore the original thread priority 
    if (pthread_setschedprio(pthread_self(), thread_priority)) {
        fprintf(stderr, "add_event(): failed to restore the thread's priority: ");
        perror(NULL);
        return;
    }
}


void print_event (event event, int task_id)
{
	time_t millis[2];
	tsConvertToMs (event.timestamp, &millis[0], &millis[1]);

	switch(event.type) {
		case TASK_BIRTH:
			printf("[%5ld.%-7ld] T%d: is born\n", millis[0], millis[1], task_id);
			break;
		case TASK_ACTIVATION:
			printf("[%5ld.%-7ld] T%d: activates\n", millis[0], millis[1], task_id);
			break;
		case TASK_BUSY:
			printf("[%5ld.%-7ld] T%d: starts ", millis[0], millis[1], task_id);
			switch(task_id) {
				case T1: 
					printf("CS(%d)\n", T1_COMP_TIME);
					break;
				case T2: 
					printf("CS(%d)\n", T2_COMP_TIME);
					break;
				case T3: 
					printf("CS(%d)\n", T3_COMP_TIME);
			}
			break;
		case TASK_FINISHED:
			printf("[%5ld.%-7ld] T%d: finishes\n", millis[0], millis[1], task_id); 
			break;
		case SERVER_ENTRY:
			printf("[%5ld.%-7ld] T%d: enters ", millis[0], millis[1], task_id);
			switch(event.server_id) {
				case S11: 
					printf("S11(%d)\n", S11_COMP_TIME);
					break;
				case S12: 
					printf("S12(%d)\n", S12_COMP_TIME);
					break;
				case S21: 
					printf("S21(%d)\n", S21_COMP_TIME);
					break;
				case S22: 
					printf("S22(%d)\n", S22_COMP_TIME);
			}
			break;
		case MUTEX_LOCK:
			printf("[%5ld.%-7ld] T%d: tries to acquire lock ", millis[0], millis[1], task_id);
			switch(event.server_id) {
				case S11: case S12: 
					printf("S1\n");
					break;
				case S21: case S22: 
					printf("S2\n");
			}
			break;
		case MUTEX_AQUIRE:
			printf("[%5ld.%-7ld] T%d: acquires lock ", millis[0], millis[1], task_id);
			switch(event.server_id) {
				case S11: case S12: 
					printf("S1\n");
					break;
				case S21: case S22: 
					printf("S2\n");
			}
			break;
		case MUTEX_RELEASE:
			printf("[%5ld.%-7ld] T%d: releases lock ", millis[0], millis[1], task_id);
			switch(event.server_id) {
				case S11: case S12: 
					printf("S1\n");
					break;
				case S21: case S22: 
					printf("S2\n");
			}
			break;
		case SERVER_EXIT:
			printf("[%5ld.%-7ld] T%d: exits ", millis[0], millis[1], task_id);
			switch(event.server_id) {
				case S11: 
					printf("S11(%d)\n", S11_COMP_TIME);
					break;
				case S12: 
					printf("S12(%d)\n", S12_COMP_TIME);
					break;
				case S21: 
					printf("S21(%d)\n", S21_COMP_TIME);
					break;
				case S22: 
					printf("S22(%d)\n", S22_COMP_TIME);
			}
			break;
		case TASK_DEATH:
			printf("[%5ld.%-7ld] T%d: dies\n", millis[0], millis[1], task_id); 
	}
}

void print_events (events_history history)
{
	event *current;
	for(current = history.first_event; current != NULL; current = current->next_event) {
		print_event(*current, history.task_id);
	}
}
