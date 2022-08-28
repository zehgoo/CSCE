#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	char* name;

	pid_t pid;
	pid = fork();

	if (pid == 0)
	{
		printf("%d started\n",getpid());
		printf("child: parent = %d\n", getppid());
		printf("child: is asleep\n");
		sleep(20);
	}
	else
	{
		// printf("child: is asleep\n");
		// sleep(20);
		// printf("child: is awake\n");
	}

	if (pid > 0)
	{
		printf("parent: %d started\n", getpid());
		printf("parent: parent = %d\n", getppid());
	}
	else
		perror("fork error");

	(pid == 0) ? (name = "child") : (name = "parent");

	printf("%s: terminating...\n", name);

	return 0;
}