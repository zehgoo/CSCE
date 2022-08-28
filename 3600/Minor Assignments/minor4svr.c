#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#define MAXLINE 1000 // max length of message

void delay(int number_of_seconds) // function for inducing delay
{
	int milli_seconds = 1000 * number_of_seconds;
	clock_t start_time = clock();
	while (clock() < start_time + milli_seconds);
}
//argc is number of arguments and argv are arguments
int main(int argc, char** argv)
{
	if(argc > 2)
	{
		printf("Please enter correct arguments");
		return 0;
	}
	int po = atoi(argv[1]);
	//stringstream po(argv[1]); // converting string to int
	int port;
	port>>po;
	char buff[100]; // creating buffer

	char *message = "Hi";
	int listenfd, len;
	struct sockaddr_in serveraddress, clientaddress;
	bzero(&serveraddress, sizeof(serveraddress));

	// Create a UDP Socket
	listenfd = socket(AF_INET, SOCK_DGRAM, 0);
	serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddress.sin_port = htons(port);
	serveraddress.sin_family = AF_INET;

	// bind server address to socket descriptor
	bind(listenfd, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
	for(;;)//Infinite for loop for infinite reciving
	{

		int r = rand() % 10; // generating random number for 30% drop simulation
		if(r<3)
		{
			printf("Eat");
			delay(1); //delay of 1 sec
			continue;
		}
		
		len = sizeof(clientaddress); //fixing size of client
		int n = recvfrom(listenfd, buff, sizeof(buff),
				0, (struct sockaddr*)&clientaddress,&len); //receive message from server
		buff[n] = '\0';
		puts(buff);
		sendto(listenfd, message, MAXLINE, 0, (struct sockaddr*)&clientaddress, sizeof(clientaddress));
		delay(1);
	}
}
