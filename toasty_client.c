#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUFFER_SIZE 256

static unsigned short port = 55555;

void talk_to_server(int sockfd)
{
	char buffer[BUFFER_SIZE];
	memset(buffer, 0, sizeof(buffer));
	
	read(sockfd, buffer, sizeof(buffer));
	printf("%s", buffer);
	
	fgets(buffer, sizeof(buffer), stdin);
	buffer[strlen(buffer) - 1] = '\0';
	
	write(sockfd, buffer, strlen(buffer));
	return;
}

int main()
{
	int serverfd;
	struct sockaddr_in server_addr;
	
	serverfd = socket(AF_INET, SOCK_STREAM, 0);
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	
	if(connect(serverfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
	{
		printf("Connection failed\n");
		return 1;
	}
	printf("Connection success!!\n");
	talk_to_server(serverfd);
	
	return 0;
}