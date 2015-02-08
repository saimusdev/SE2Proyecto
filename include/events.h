/*******************************************************************************

File: events.h

Author: Simon Ortego Parra

*******************************************************************************/

#ifndef EVENTS_H
#define EVENTS_H

#define BIRTH 0
#define ACTIVATION 1
#define T1_EXECUTING 2
#define T2_EXECUTING 3
#define T3_EXECUTING 4
#define COMPLETION 5
#define S11_ENTRY 6
#define S12_ENTRY 7
#define S21_ENTRY 8
#define S22_ENTRY 9
#define S11_EXIT 10 
#define S12_EXIT 11
#define S21_EXIT 12 
#define S22_EXIT 13 
#define DEATH 14

typedef struct event {
    int type;
    struct timespec timestamp;
    struct event *next_event;
} event;

typedef struct events_history {
	int task_id, task_comp_time;
	event *first_event, *last_event;
} events_history;

events_history *create_events_history (int task_id);

void clear_history (events_history *history);

void add_event (int type, events_history *history);

void print_events (events_history history);

#endif /* EVENTS_H */
