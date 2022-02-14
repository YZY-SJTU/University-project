#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main(){
	pid_t pid = fork();
	if(pid < 0)
	{
		//error occurred		
		printf("Fork failed\n");
		return 1;
	}
	else if(pid == 0)
		{
			//child process		
			pid_t pid_name = getpid();
			printf("519030910168 Child: %d\n", pid_name);		
			execl("/data/misc/ptreeARM", "ptreeARM", NULL);
		}	
	  	else
		{
			//parent process
			pid_t pid_name = getpid();
			printf("519030910168 Parent: %d\n", pid_name);
		}
	return 0;
}

