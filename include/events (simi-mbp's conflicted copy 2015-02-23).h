/*******************************************************************************

File: events.h

Author: Simon Ortego Parra

*******************************************************************************/

#ifndef EVENTS_H
#define EVENTS_H

#define TASK_BIRTH 0
#define TASK_ACTIVATION 1
#define TASK_BUSY 2
#define TASK_FINISHED 3
#define SERVER_ENTRY 4
#define MUTEX_LOCK 5
#define MUTEX_AQUIRE 6
#define MUTEX_RELEASE 7
#define SERVER_EXIT 8
#define TASK_DEATH 9

typedef struct event {
    unsigned char type, server_id; 
    struct timespec timestamp;
    struct event *next_event;
} event;

typedef struct events_history {
	int task_id, task_comp_time;
	event *first_event, *last_event;
} events_history;

events_history *create_events_history (int task_id);

void clear_history (events_history *history);

void add_event (unsigned char type, unsigned char server_id, events_history *history);

void print_events (events_history history);

#endif /* EVENTS_H */
