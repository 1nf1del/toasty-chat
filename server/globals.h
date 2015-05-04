#ifndef _GLOBALS_H_
#define _GLOBALS_H_

extern struct client_node *clients;
extern pthread_mutex_t clients_lock;
extern pthread_mutex_t console_lock;

#endif