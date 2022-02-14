#include <stdio.h>
#include<stdlib.h>

#define __NR_hellocall 356
#define MaxBufferSize 1024

struct prinfo{
	pid_t parent_pid;		/*process id of parent*/
	pid_t pid;			/*process id*/
	pid_t first_child_pid;		/*pid of youngest child*/
	pid_t next_sibling_pid;		/*pid of older sibling*/
	long state;			/*current state of process*/
	long uid;			/*user id of process owner*/
	char comm[64];			/*name of program executed*/
};

void print_ptree(struct prinfo *buf, int *nr){
	//find num of tabs	
	int tabs[MaxBufferSize], pid[MaxBufferSize];
	int i, j;
	for(i=0; i<MaxBufferSize; ++i)
	{
		tabs[i] = 0;
		pid[i] = buf[i].pid;
	}
	int temp_parent;

	for(i=1; i<*nr; ++i)
	{		
		temp_parent = buf[i].parent_pid;
		j = i - 1;
		while(j>=0 && temp_parent != pid[j])
			j--;
		if(j>=0)
			tabs[i] = tabs[j] + 1;
	}

	//print
	for(i=0; i<*nr; i++)
	{
		for(j=0;j<tabs[i]; j++)
			printf("\t");
		printf("%s, %d, %ld, %d, %d, %d, %d\n", buf[i].comm, buf[i].pid, buf[i].state, buf[i].parent_pid, buf[i].first_child_pid, buf[i].next_sibling_pid, buf[i].uid);
	}
}

int main(){
	struct prinfo *buf = malloc(MaxBufferSize*sizeof(struct prinfo));
	int *nr = malloc(sizeof(int));//allocate memory space
	syscall(__NR_hellocall, buf, nr);
	print_ptree(buf, nr);

	free(buf);
	free(nr);
	return 0;
}
