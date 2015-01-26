/*******************************************************************************

File: events.h

Author: Simon Ortego Parra

*******************************************************************************/

#ifndef EVENTS_H
#define EVENTS_H

#define ACTIVATES 0
#define ENTER_CS 1
#define EXIT_CS 2

typedef struct event {
    int type;
    struct timespec timestamp;
    struct event *next_event;
} event;

typedef struct events_history {
	int task_id;
	event *first_event, *last_event;
} events_history;

events_history *create_events_history (int task_id);

void clear_history (events_history *history);

void add_event (int event_id, struct timespec timestamp, events_history *history);

void print_events (events_history history);

#endif /* EVENTS_H */
