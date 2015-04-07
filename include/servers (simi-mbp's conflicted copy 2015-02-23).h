/*******************************************************************************

File: servers.h

Author: Simon Ortego Parra

*******************************************************************************/

#ifndef SERVERS_H
#define SERVERS_H

void create_servers (void);

/* Server 1 */
#define S11 11
#define S12 12
#define S11_COMP_TIME 10
#define S12_COMP_TIME 20
void s11 (int task_id, events_history *history);
void s12 (int task_id, events_history *history);

/* Server 2 */
#define S21 21
#define S22 22
#define S21_COMP_TIME 30
#define S22_COMP_TIME 20
void s21 (int task_id, events_history *history);
void s22 (int task_id, events_history *history);

#endif /* SERVERS_H */
