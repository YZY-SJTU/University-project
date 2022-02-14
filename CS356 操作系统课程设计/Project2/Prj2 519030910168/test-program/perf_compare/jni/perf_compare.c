#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <linux/unistd.h>
#include <linux/sched.h>
#include <ctype.h>
#include <time.h>
#include <sys/time.h>
void test_little(void)
{
  int i,j,k;
  int sum = 0;
  for(k = 0; k < 30; k++) 
  for(j = 0; j < 30; j++) 
  for(i = 0; i < 30; i++) 
    sum += i; 
}

void test_medium(void)
{
  int i,j,k;
  int sum = 0;
  for(k = 0; k < 6000; k++)
  for(j = 0; j < 6000; j++) 
  for(i = 0; i < 6000; i++) 
    test_little(); 
}

void test_high(void)
{
  int i,j,k;
  int sum = 0;
  for(k = 0; k < 900000; k++)
  for(j = 0; j < 900000; j++) 
  for(i = 0; i < 900000; i++) 
    test_medium();
}

void test_hi(void)
{
  int i,j,k;
  int sum = 0;
  for(k = 0; k < 120000000; k++)
  {
	test_high();  	
	for(j = 0; j < 120000000; j++) 
  	{
		test_high();	
		for(i = 0; i < 120000000; i++) 
	    	test_high();
  	}
  }  
}

int main(void)
{
  int i, pid, result1, result2, result3;
  int tmp;
  int schedule, task;
  struct sched_param param;
  struct timeval start, end;


  //Set scheduler and priority.
  printf("choose the schedule policy(0-NORAMAL, 1-FIF0, 2-RR, 6-WRR):");
  scanf("%d", &schedule);
  printf("choose the schedule priority:");
  scanf("%d", &tmp);
  if(schedule != 6)
	param.sched_priority = tmp;
  else 
	param.sched_priority = 0;
	
  printf("choose the task scale(1-little, 2-medium, 3-high, 4-hi):");
  scanf("%d", &task);
    
    	

    result1 = fork();
    if(result1 == 0)
    {
    	result2 = fork();
   	if(result2 == 0)
	{
			result3 = fork();		
			if(result3 == 0)
			{			
				sched_setscheduler(getpid(), schedule, &param);
				gettimeofday(&start, NULL);						
    				printf("start_sec:%d\n", start.tv_sec);
    				printf("start_usec:%d\n", start.tv_usec);
				printf("child parent=%d current=%d\n", getppid(), getpid());
				switch(task)
				{
					case 1: test_little(); break;
					case 2: test_medium(); break;
					case 3: test_high(); break;
					case 4: test_hi(); break;
				}
			}
			else 
			{			
				sched_setscheduler(getpid(), schedule, &param);				
				printf("child parent=%d current=%d\n", getppid(), getpid());			
				switch(task)
				{
					case 1: test_little(); break;
					case 2: test_medium(); break;
					case 3: test_high(); break;
					case 4: test_hi(); break;
				}
				wait(NULL);
			}
	}  	
	else
	{	
		sched_setscheduler(getpid(), schedule, &param);		
		printf("child parent=%d current=%d\n", getppid(), getpid());
		switch(task)
		{
		case 1: test_little(); break;
		case 2: test_medium(); break;
		case 3: test_high(); break;
		case 4: test_hi(); break;
		}
		wait(NULL);		
	}
    }
    else
    {
      sched_setscheduler(getpid(), schedule, &param);
      printf("parent parent=%d current=%d child=%d\n", getppid(), getpid(), result1);
      switch(task)
	{
	case 1: test_little(); break;
	case 2: test_medium(); break;
	case 3: test_high(); break;
	case 4: test_hi(); break;
	}
      wait(NULL);
      gettimeofday(&end, NULL);
      printf("end_sec:%d\n", end.tv_sec);
      printf("end_usec:%d\n", end.tv_usec);
    }

  return 0;
}
