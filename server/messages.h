#ifndef _MESSAGES_H_
#define _MESSAGES_H_

extern const char *MALLOC_FAILURE;
extern const char *SOCKET_ERROR;
extern const char *CLIENT_COMM_FAILURE;

void distribute_message ( struct client_node *sender, const char *msg );

#endif
