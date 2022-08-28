#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>
#include <time.h>
#define MAXLINE 1000

void delay(int number_of_seconds) // function for inducing delay
{
	int milli_seconds = 1000 * number_of_seconds;
	clock_t start_time = clock();
	while (clock() < start_time + milli_seconds);
}

int main(int argc, char** argv)
{
	if(argc > 3)
	{
		printf("Please enter correct arguments");
		return 0;
	}

	int po = atoi(argv[2]);
	//stringstream po(argv[2]); // converting string to int
	int port;
	port>>po;
	char buffer[100];
	char *message = "sent message";//message to be sent by client
	int sockfd, n;
	struct sockaddr_in serveraddress;

	// clear serveraddress
	bzero(&serveraddress, sizeof(serveraddress));
	serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1");
	serveraddress.sin_port = htons(port);
	serveraddress.sin_family = AF_INET;

	// create datagram socket
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	// connect to server
	if(connect(sockfd, (struct sockaddr *)&serveraddress, sizeof(serveraddress)) < 0)
	{
		printf("\n Error : Connect Failed \n");
		exit(0);
	}

	// requesting server to send message
	// connecting stores the peers IP and port
	for(int i=0;i<10;i++) //sending 10 messages to the server
	{
		delay(1); // waiting 1 second for reviving message
		recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)NULL, NULL);
		puts(buffer);

		if(buffer=="\n")
		{
			continue;
		}
		sendto(sockfd, message, MAXLINE, 0, (struct sockaddr*)NULL, sizeof(serveraddress));
	}

	double t1=0.0, t2=0.0; // for calculating rrt time
	struct timeval start, end;
	char* command;
	char reply[BUFSIZ];
	for(int num_packet_sent=0;num_packet_sent<100;num_packet_sent++)
	{
		if(gettimeofday(&start,NULL)) // getting time of delay
		{
			printf("time failed\n");
			return 0;
		}

		send(sockfd, command, sizeof(char),0);
		ssize_t optval = 0;
		optval =  recv(sockfd, reply, sizeof(char),0);
		if(optval==-1) 
		{
			perror("Receive error");
			exit(1);
		}
		else
		{
			if(gettimeofday(&end,NULL)) 
			{
				printf("time failed\n");
				return 0;;
			}

			t1+=start.tv_sec+(start.tv_usec/1000000.0);
			t2+=end.tv_sec+(end.tv_usec/1000000.0);
		}
	}
	//calculate and print mean rtt
	printf("RTT = %g ms\n",(t2-t1)/100);
	close(sockfd);// closing the port

	return 0;
}