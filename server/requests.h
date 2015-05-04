#ifndef _REQUESTS_H_
#define _REQUESTS_H_

#define REQUEST_EXIT 0
#define REQUEST_USERS 1
#define REQUEST_VERSION 2
#define REQUEST_WHISPER 3

int process_request ( struct client_node *client, char *msg_buffer );

#endif
