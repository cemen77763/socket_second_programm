#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>

#define handle_error(msg)\
 do { perror(msg); exit(EXIT_FAILURE); } while(0);

 int main(){
 	int sfd;
 	char buff[255];
 	struct sockaddr_in peer_addr;
 	socklen_t peer_addr_size;

 	sfd = socket(AF_INET, SOCK_DGRAM, 0);
 	if (sfd == -1)
 		handle_error("socket");

 	peer_addr.sin_family = AF_INET;
 	peer_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
 	peer_addr.sin_port = htons(5000);
 	peer_addr_size = sizeof(struct sockaddr_in);

 	buff[0] = 'H'; buff[1] = 'e'; buff[2] = 'l'; buff[3] = 'l'; buff[4] = 'o'; buff[5] = '!'; buff[6] = '\0';
 	if (sendto(sfd, buff, 255, 0, (struct sockaddr*) &peer_addr, peer_addr_size) == -1)
 		handle_error("sendto");

 	if (recvfrom(sfd, buff, 255, 0, (struct sockaddr*) &peer_addr, &peer_addr_size) == -1)
 		handle_error("recvfrom");
 	printf("I receive %s\n", buff);

 	close(sfd);
 	exit(EXIT_SUCCESS);
 }