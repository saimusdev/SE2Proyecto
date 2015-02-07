/*******************************************************************************

File: events.h

Author: Simon Ortego Parra

*******************************************************************************/

#ifndef EVENTS_H
#define EVENTS_H

#define TASK_BIRTH 0
#define TASK_ACTIVATION 1
#define TASK_COMPLETION 2
#define S1_ENTRY 3
#define S2_ENTRY 4
#define CS_EXIT 5
#define TASK_DEATH 6

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

void add_event (int type, events_history *history);

void print_events (events_history history);

#endif /* EVENTS_H */
