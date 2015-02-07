/*******************************************************************************

File: servers.h

Author: Simon Ortego Parra

*******************************************************************************/

#ifndef SERVERS_H
#define SERVERS_H

void create_servers (void);

/* Server 1 */
#define S11_COMP_TIME 10
#define S12_COMP_TIME 20
void server1_func_1 (int task_id, events_history *history);
void server1_func_2 (int task_id, events_history *history);

/* Server 2 */
#define S21_COMP_TIME 30
#define S22_COMP_TIME 20
void server2_func_1 (int task_id, events_history *history);
void server2_func_2 (int task_id, events_history *history);

#endif /* SERVERS_H */
