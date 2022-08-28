#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main()
{

	pid_t pid;
	pid = fork();

	if (pid == 0) // child process 
	{
		exit(0);
	}
	else if (pid > 0) // parent process
	{
		sleep(5);
		system("ps -e -o pid,ppid,stat,user,cmd | grep $USER");
	}
	else
		perror("fork error");

	return 0;
}

