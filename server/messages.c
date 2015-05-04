#include <stdio.h>
#include <pthread.h>
#include <sys/socket.h>
#include "clients.h"
#include "globals.h"
#include "../shared/constants.h"

const char *MALLOC_FAILURE = "Failed to allocate memory\n";
const char *SOCKET_ERROR = "Failed to initialize socket\n";
const char *CLIENT_COMM_FAILURE = "Failed to communicate with client\n";


void distribute_message ( struct client_node *sender, const char *msg )
{
        struct client_node *cur = clients;

        pthread_mutex_lock ( &clients_lock );
        while ( cur )
        {
                if ( cur != sender )
                {
                        if ( send ( cur->sockfd, msg, BUFFER_SIZE, 0 ) == -1 )
                        {
                                perror ( CLIENT_COMM_FAILURE );
                        }
                }
                cur = cur->next_client;
        }
        pthread_mutex_unlock ( &clients_lock );

        return;
}

