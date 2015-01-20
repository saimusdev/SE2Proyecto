/*******************************************************************************

File: events.h

Author: Simon Ortego Parra

*******************************************************************************/

#include <stdlib.h>
#include <stdio.h>

#include "events.h"
#include "ts_util.h"


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

void add_event (int event_id, struct timespec timestamp, events_history *history)
{
	event *new_event;
	new_event = malloc(sizeof(event));
	if (new_event != NULL) {
		/* if could allocate memory for the new event */
		new_event->event_id = event_id;
		new_event->timestamp = timestamp;
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
        fprintf(stderr, "add_event(): could not allocate memory for new event");
	}
}

void print_events (events_history *history)
{
	event *current;
	for(current = history->first_event; current != NULL; current = current->next_event) {
		switch(current->event_id) {
			case ENTER_CS:
				printf("[%ld] T%d: enters cs\n", tsConvertToMs(current->timestamp), history->task_id);
				break;
			case EXIT_CS:
				printf("[%ld] T%d: exits cs\n", tsConvertToMs(current->timestamp), history->task_id);
				break;
			default:
				break;
		}
	}
}

