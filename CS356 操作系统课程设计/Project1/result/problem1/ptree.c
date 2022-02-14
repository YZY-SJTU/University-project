#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/sched.h>
#include<linux/unistd.h>
#include<linux/list.h>
#include<linux/slab.h>
#include<linux/uaccess.h>

MODULE_LICENSE("Dual BSD/GPL");
#define __NR_hellocall 356
#define MaxBufferSize 1024

static int (*oldcall)(void);

struct prinfo{
	pid_t parent_pid;		/*process id of parent*/
	pid_t pid;			/*process id*/
	pid_t first_child_pid;		/*pid of youngest child*/
	pid_t next_sibling_pid;		/*pid of older sibling*/
	long state;			/*current state of process*/
	long uid;			/*user id of process owner*/
	char comm[64];			/*name of program executed*/
};

//translate task_struct and input into the prinfo
void input_prinfo(struct task_struct *source, struct prinfo *target){
	target->parent_pid = source->parent->pid;

	target->pid = source->pid; 
	
	if(list_empty(&(source->children))) target->first_child_pid = 0;
	else target->first_child_pid = list_entry((&source->children)->next, struct task_struct, sibling)->pid;
	
	if(list_empty(&(source->sibling))) target->next_sibling_pid = 0;
	else target->next_sibling_pid = list_entry((&source->sibling)->next, struct task_struct, sibling)->pid;
	
	target->state = source->state;

	target->uid = source->cred->uid;

	get_task_comm(target->comm, source);
}

void DFS(struct task_struct *source, struct prinfo *buf, int *nr){
	struct task_struct *temp;
	struct list_head *head;
	
	input_prinfo(source, &buf[*nr]);
	(*nr)++;	
	
	list_for_each(head, &source->children) //search the whole process
	{
		temp = list_entry(head, struct task_struct, sibling);
		DFS(temp, buf, nr);
	}
	
}

static int ptree(struct prinfo *buf, int *nr){
	
	//initialization	
	struct prinfo *kbuf = kcalloc(MaxBufferSize, sizeof(struct prinfo), GFP_KERNEL);
	int *num = kzalloc(sizeof(int), GFP_KERNEL);
	*num = 0;
	
	//dfs and input prinfo
	read_lock(&tasklist_lock);
	DFS(&init_task,kbuf,num);
	read_unlock(&tasklist_lock);
	
	//print to kernel
	if(copy_to_user(buf, kbuf, MaxBufferSize*sizeof(struct prinfo))){
		printk("Copy error happened!\n");	
		return 1;	
	}
	if(copy_to_user(nr, num, sizeof(int))){
		printk("Copy error happened!\n");	
		return 1;	
	}
	//release space
	kfree(kbuf);
	kfree(num);

	return 0;
}
	
static int addsyscall_init(void)
{
	long *syscall = (long*)0xc000d8c4;
	oldcall = (int(*)(void))(syscall[__NR_hellocall]);
	syscall[__NR_hellocall] = (unsigned long )ptree;
	printk(KERN_INFO "module load!\n");
	return 0;

}

static void addsyscall_exit(void)
{
	long *syscall = (long*)0xc000d8c4;
	syscall[__NR_hellocall] = (unsigned long )oldcall;
	printk(KERN_INFO "module exit!\n");
}

module_init(addsyscall_init);
module_exit(addsyscall_exit);
