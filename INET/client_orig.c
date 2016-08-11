#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

void error(char *msg)
{
	perror(msg);
	exit(0);
}

int main(int argc, char *argv[])
{
	int sockfd, portno, n;

	struct sockaddr_in serv_addr;
	struct hostent *server;

	char buffer[256];
	if (argc < 2) {
		fprintf(stderr,"usage %s hostname port\n", argv[0]);
		exit(0);
	}
	portno = atoi(argv[1]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
		error("ERROR opening socket");
	//server = gethostbyname(argv[1]);
	if (server == NULL) {
		fprintf(stderr,"ERROR, no such host\n");
		exit(0);
	}
	memset((char *) &serv_addr,0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	//bcopy((char *)server->h_addr, 
	//   (char *)&serv_addr.sin_addr.s_addr,
	//  server->h_length);
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	serv_addr.sin_port = htons(portno);
	if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
		error("ERROR connecting");
        perror("connect");
	printf("Please enter the message: ");
	memset(buffer,0,256);
	fgets(buffer,255,stdin);
	printf("message: %s",buffer);
	n = write(sockfd,buffer,strlen(buffer));
	if (n < 0) 
		error("ERROR writing to socket");
	memset(buffer,0,256);
	n = read(sockfd,buffer,255);
	if (n < 0) 
		error("ERROR reading from socket");
	printf("%s\n",buffer);
	return 0;
}
