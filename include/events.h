/*******************************************************************************

File: events.h

Author: Simon Ortego Parra

*******************************************************************************/

#ifndef EVENTS_H
#define EVENTS_H

#define ENTER_CS 0
#define EXIT_CS 1

typedef struct event {
    int event_id;
    struct timespec timestamp;
    struct event *next_event;
} event;

typedef struct event_history {
	int task_id;
	struct event *first_event, *last_event;
} event_history;

event_history *create_event_history (int task_id);

void clear_history (event_history *history);

void add_event (int event_id, struct timespec timestamp, event_history *history);

void print_events (event_history *history);

#endif /* EVENTS_H */
