/*******************************************************************************

File: events.h

Author: Simon Ortego Parra

*******************************************************************************/

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "events.h"
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
		case TASK_ACTIVATION:
			printf("[%2ld.%ld ms ] T%d: activates\n", millis[0], millis[1], task_id);
			break;
		case TASK_COMPLETION:
			printf("[%2ld.%ld ms ] T%d: completes\n", millis[0], millis[1], task_id); 
			break;
		case CS_ENTRY:
			printf("[%2ld.%ld ms ] T%d: enters cs\n", millis[0], millis[1], task_id); 
			break;
		case CS_EXIT:
			printf("[%2ld.%ld ms ] T%d: exits cs\n",  millis[0], millis[1], task_id);
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
