#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
void sighandler(int);
int main()
{
	
	int pipefd1[2]; 
	int pipefd2[2];
	int pipefd3[2];
    	char stuID[100];
    	char roomNUM[100];
    	char name[100];
    	signal(SIGINT, sighandler);

	if (pipe(pipefd1) == -1) 
  	{
		fprintf(stderr, "Pipe 1 Failed");
		return 1;
	}
	if (pipe(pipefd2) == -1) 
 	{
		fprintf(stderr, "Pipe 2 Failed");
		return 1;
	}
	if (pipe(pipefd3) == -1) 
  	{
		fprintf(stderr, "Pipe 3 Failed");
		return 1;
	}
	
	pid_t pid1 = fork();
	pid_t pid2 = fork();

	if (pid1 > 0 && pid2 > 0) 
  	{
		close(pipefd1[0]);
		close(pipefd2[0]);
		close(pipefd3[0]);
		
		printf("Enter Your Student ID: \n");
        	scanf("%s", stuID); 
        	printf("\n");
        	printf("Enter Room Number: \n");
        	scanf("%s", roomNUM);
        	printf("\n");
        	printf("Enter Name: \n");
        	scanf("%s", name); 
        	printf("\n");
        
        	write(pipefd1[1], stuID, 100);
        	write(pipefd2[1], roomNUM, 100);
        	write(pipefd3[1], name, 100);
        
        	close(pipefd1[1]);
        	close(pipefd2[1]);
        	close(pipefd3[1]);
		wait(NULL);
	}
	else if (pid1 == 0 && pid2 > 0)
	{
		close(pipefd1[1]);
		read(pipefd1[0], stuID, 100);
		printf("Your Student ID: %s \n", stuID);
		close(pipefd1[0]);
	}
	else if (pid1 > 0 && pid2 == 0)
	{
		close(pipefd2[1]);
		read(pipefd2[0], roomNUM, 100);
		printf("Your Room Number: %s \n", roomNUM);
		close(pipefd2[0]);
		
	}
	else 
	{
		close(pipefd3[1]);
		read(pipefd3[0], name, 100);
		printf("Your Name: %s \n", name);
		close(pipefd3[0]);
	}
	return 0;
}
void sighandler(int sig) {
   printf("Signal End\n");
   exit(1);
}
