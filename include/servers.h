/*******************************************************************************

File: servers.h

Author: Simon Ortego Parra

*******************************************************************************/

#ifndef _SERVERS_H
#define _SERVERS_H

void create_servers (void);

/* Server 1
#define S11_COMP_TIME 10
#define S11_COMP_TIME 20  */
#define S11_COMP_TIME 100
#define S12_COMP_TIME 200
void server1_func_1 (unsigned char task_id);
void server1_func_2 (unsigned char task_id);

/* Server 2
#define S11_COMP_TIME 30
#define S11_COMP_TIME 20  */
#define S21_COMP_TIME 300
#define S22_COMP_TIME 200
void server2_func_1 (unsigned char task_id);
void server2_func_2 (unsigned char task_id);


#endif /* _SERVERS_H */
