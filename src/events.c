/******************************************************************************* 
File: events.h

Author: Simon Ortego Parra

*******************************************************************************/

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

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

void add_event (int type, events_history *history)
{
    struct timespec timestamp;
	event *new_event;

   	clock_gettime(CLOCK_REALTIME, &timestamp);   
	new_event = malloc(sizeof(event));

	if (new_event != NULL) {
		/* if could allocate memory for the new event */
		new_event->type = type;
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
}

void print_event (event event, int task_id)
{
	time_t millis[2];
	tsConvertToMs (event.timestamp, &millis[0], &millis[1]);

	switch(event.type) {
		case BIRTH:
			printf("[%5ld.%-7ld] T%d: is born\n", millis[0], millis[1], task_id);
			break;
		case ACTIVATION:
			printf("[%5ld.%-7ld] T%d: activates\n", millis[0], millis[1], task_id);
			break;
		case T1_EXECUTING:
			printf("[%5ld.%-7ld] T1: executing CS(%d)\n", millis[0], millis[1], T1_COMP_TIME);
			break;
		case T2_EXECUTING:
			printf("[%5ld.%-7ld] T2: executing CS(%d)\n", millis[0], millis[1], T2_COMP_TIME);
			break;
		case T3_EXECUTING:
			printf("[%5ld.%-7ld] T3: executing CS(%d)\n", millis[0], millis[1], T3_COMP_TIME);
			break;
		case COMPLETION:
			printf("[%5ld.%-7ld] T%d: finishes\n", millis[0], millis[1], task_id); 
			break;
		case S11_ENTRY:
			printf("[%5ld.%-7ld] T%d: enters S11(%d)\n", millis[0], millis[1], task_id, S11_COMP_TIME);
			break;
		case S12_ENTRY:
			printf("[%5ld.%-7ld] T%d: enters S12(%d)\n", millis[0], millis[1], task_id, S12_COMP_TIME);
			break;
		case S21_ENTRY:
			printf("[%5ld.%-7ld] T%d: enters S21(%d)\n", millis[0], millis[1], task_id, S21_COMP_TIME);
			break;
		case S22_ENTRY:
			printf("[%5ld.%-7ld] T%d: enters S22(%d)\n", millis[0], millis[1], task_id, S22_COMP_TIME);
			break;
		case S11_EXIT:
			printf("[%5ld.%-7ld] T%d: exits S11\n", millis[0], millis[1], task_id);
			break;
		case S12_EXIT:
			printf("[%5ld.%-7ld] T%d: exits S12\n", millis[0], millis[1], task_id);
			break;
		case S21_EXIT:
			printf("[%5ld.%-7ld] T%d: exits S21\n", millis[0], millis[1], task_id);
			break;
		case S22_EXIT:
			printf("[%5ld.%-7ld] T%d: exits S22\n", millis[0], millis[1], task_id);
			break;
		case DEATH:
			printf("[%5ld.%-7ld] T%d: dies\n",  millis[0], millis[1], task_id);
			break;
		default:
			break;
	}
}

void print_events (events_history history)
{
	event *current;
	for(current = history.first_event; current != NULL; current = current->next_event) {
		print_event(*current, history.task_id);
	}
}
