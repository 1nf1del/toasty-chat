#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "clients.h"
#include "../shared/constants.h"
#include "globals.h"
#include "messages.h"


struct client_node *add_client ( int sockfd )
{
        struct client_node *cur = clients;
        struct client_node *new_client = malloc ( sizeof ( struct client_node ) );

        if ( !new_client )
        {
                perror ( MALLOC_FAILURE );
                return NULL;
        }

        new_client->sockfd = sockfd;
        new_client->next_client = NULL;
        new_client->username = malloc ( USERNAME_SIZE );
        memset ( new_client->username, 0, USERNAME_SIZE );

        pthread_mutex_lock ( &clients_lock );

        while ( cur && cur->next_client )
        {
                cur = cur->next_client;
        }
        if ( !cur )
        {
                cur = new_client;
        }
        else
        {
                cur->next_client = new_client;
        }

        pthread_mutex_unlock ( &clients_lock );

        return new_client;
}

void remove_client ( struct client_node *client )
{
        struct client_node *cur;

        cur = clients;

        pthread_mutex_lock ( &clients_lock );

        if ( !cur || !client )
        {
                return;
        }

        while ( cur && cur->next_client )
        {
                if ( cur == client )
                {
                        cur->next_client = client->next_client;
                        free_client ( client );
                }
        }

        pthread_mutex_unlock ( &clients_lock );
}

void free_client ( struct client_node *client )
{
        free ( client->username );
        free ( client );
}
