#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <linux/unistd.h>
#include <linux/sched.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h> /* high-res timers */
#include <sched.h> /* for std. scheduling system calls */

#define SCHED_NORMAL        0
#define SCHED_FIFO      1
#define SCHED_RR        2
#define SCHED_BATCH     3
#define SCHED_IDLE      5
#define SCHED_WRR       6

static void change_scheduler()
{
	int result, tmp;
	struct sched_param param;
	pid_t pid;
	int policy, oldpolicy;
	
	printf("Input the process id (PID) you want to modify: ");
	scanf("%d", &tmp);
	pid = tmp;
	if (!pid) 
	{
        	//perror("Invalid PID. Aborting...");
		printf("Invalid PID. Aborting...");
        	exit(-1);
	}
	oldpolicy = sched_getscheduler(pid);
	printf("Please input the choice of Scheduling policy algorithms (0-NORAMAL, 1-FIF0, 2-RR, 6-WRR): ");
	scanf("%d", &policy);
	if(policy != 0 && policy != 1 && policy != 2 && policy != 6)
	{
		//perror("Wrong Schedule Policy. Aborting...");
		printf("Wrong Schedule Policy. Aborting...");
        	exit(-1);
	}
	
	printf("Set process's priority(1-99): ");
	scanf("%d", &tmp);
	if(policy != 6)
		param.sched_priority = tmp;
	else 
		param.sched_priority = 0;
	
	printf("Changing Scheduler for PID %d\n", pid);
	result = sched_setscheduler(pid, policy, &param);
	if(result < 0)
	{
		//perror("Changing Scheduler failed. Aborting...");
		printf("Changing Scheduler failed. Aborting...");
        	exit(-1);
	}
	printf("successfully Switched!\n");
	printf("current scheduler's priority is :%d\n", param.sched_priority);
	printf("old policy: ");
	switch(oldpolicy)
	{
		case 0: printf("normal \n"); break;
		case 1: printf("fifo \n"); break;
		case 2: printf("rr \n"); break;
		case 3: printf("batch \n"); break;
		case 5: printf("idle \n"); break;
		case 6: printf("wrr \n"); break;
	}
	printf("current policy: ");
	switch(policy)
	{
		case 0: printf("normal \n"); break;
		case 1: printf("fifo \n"); break;
		case 2: printf("rr \n"); break;
		case 3: printf("batch \n"); break;
		case 5: printf("idle \n"); break;
		case 6: printf("wrr \n"); break;
	}
}

int main(){
	change_scheduler();
	return 0;
}

