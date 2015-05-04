#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <sys/socket.h>
#include "clients.h"
#include "../shared/constants.h"
#include "globals.h"
#include "requests.h"

int process_request ( struct client_node *client, char *msg_buffer )
{
        int request = * ( ( int * ) msg_buffer + 1 );

        switch ( request )
        {
                case REQUEST_EXIT:
                        close ( client->sockfd );
                        remove_client ( client );
                        pthread_kill ( pthread_self(), SIGKILL );
                        break;
                case REQUEST_USERS:
                        ;
                        struct client_node *cur = clients;
                        char buffer[BUFFER_SIZE];

                        memset ( buffer, 0, BUFFER_SIZE );
                        strncpy ( buffer, "Current users:\n", BUFFER_SIZE );

                        pthread_mutex_lock ( &clients_lock );
                        while ( cur )
                        {
                                strncat ( buffer, cur->username, BUFFER_SIZE );
                                strncat ( buffer, "\n", BUFFER_SIZE );
                                cur = cur->next_client;
                        }
                        pthread_mutex_unlock ( &clients_lock );

                        send ( client->sockfd, buffer, BUFFER_SIZE, 0 );
                        break;
                case REQUEST_VERSION:
                        break;
                case REQUEST_WHISPER:
                        break;
                default:
                        return 1;
        }
        return 0;
}
