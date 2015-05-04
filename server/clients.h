#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <pthread.h>

struct client_node
{
        int sockfd;
        char *username;
        struct client_node *next_client;
};

extern pthread_mutex_t clients_lock;

struct client_node *add_client ( int sockfd );
void remove_client ( struct client_node *client );
void free_client ( struct client_node *client );

#endif
