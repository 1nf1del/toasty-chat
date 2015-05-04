#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "clients.h"
#include "../shared/constants.h"
#include "messages.h"
#include "requests.h"

struct client_node *clients;
pthread_mutex_t clients_lock;
pthread_mutex_t console_lock;

void *serve_client ( void *client_ptr )
{
        struct client_node *client = ( struct client_node * ) client_ptr;
        char buffer[BUFFER_SIZE];

        if ( recv ( client->sockfd, buffer, USERNAME_SIZE, 0 ) == -1 )
        {
                perror ( CLIENT_COMM_FAILURE );
                close ( client->sockfd );
                remove_client ( client );
                return NULL;
        }

        strncpy ( client->username, buffer, BUFFER_SIZE );

        while ( 1 )
        {
                if ( recv ( client->sockfd, buffer, BUFFER_SIZE, 0 ) < 1 )
                {
                        perror ( CLIENT_COMM_FAILURE );
                        continue;
                }

                if ( *buffer == '/' )
                {
                        if ( process_request ( client, buffer ) != 0 )
                        {
                                pthread_mutex_lock ( &clients_lock );
                                distribute_message ( client, buffer );
                                pthread_mutex_unlock ( &clients_lock );
                        }
                }

                return NULL;
        }
}

int main()
{
        int serverfd;
        int clientfd;
        struct sockaddr_in server_addr;
        pthread_t thread;

        serverfd = socket ( AF_INET, SOCK_STREAM, 0 );
        if ( serverfd == -1 )
        {
                perror ( SOCKET_ERROR );
                exit ( 1 );
        }

        memset ( &server_addr, 0, sizeof ( server_addr ) );
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = htonl ( INADDR_ANY );
        server_addr.sin_port = htons ( PORT );

        if ( bind ( serverfd, ( struct sockaddr * ) &server_addr, sizeof ( server_addr ) ) == -1 )
        {
                perror ( SOCKET_ERROR );
                exit ( 1 );
        }

        if ( listen ( serverfd, CLIENTS_MAX ) )
        {
                perror ( SOCKET_ERROR );
                exit ( 1 );
        }

        pthread_mutex_init ( &clients_lock, NULL );
        pthread_mutex_init ( &console_lock, NULL );

        while ( 1 )
        {
                clientfd = accept ( serverfd, ( struct sockaddr * ) NULL, NULL );
                if ( clientfd == -1 )
                {
                        perror ( CLIENT_COMM_FAILURE );
                }

                struct client_node *new_client = add_client ( clientfd );

                pthread_create ( &thread, NULL, &serve_client,  new_client );
        }

        return 0;
}
