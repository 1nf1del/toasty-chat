#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define CLIENTS_MAX 5

static unsigned short port = 55555;


void talk_to_client(int sockfd)
{
	char buffer[256];
	memset(buffer, 0, sizeof(buffer));
	
	write(sockfd, "Welcome to toasty server\nEnter some words: ", 44);
	read(sockfd, buffer, 256);
	
	printf("Client says: %s\n", buffer);
	return;
}

int main()
{
	int serverfd;
	int clientfd;
	struct sockaddr_in server_addr;
	pid_t pid;
	
	serverfd = socket(AF_INET, SOCK_STREAM, 0);
	
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(port);
	
	bind(serverfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
	listen(serverfd, CLIENTS_MAX);
	
	while(1)
	{
		clientfd = accept(serverfd, (struct sockaddr *)NULL, NULL);
		pid = fork();
		if(pid < 0)
		{
			printf("Forking failure\n");
			exit(1);
		}
		else if (pid > 0)
		{
			close(clientfd);
			continue;
		}
		else
		{
			close(serverfd);
			talk_to_client(clientfd);
			break;
		}
	}
	
	return 0;
}