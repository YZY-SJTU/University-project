/*
 * WRR Scheduling Class 
 */

#include"sched.h"

#include<linux/slab.h>

/*
 * Update the current task's runtime statistics. Skip current tasks that
 * are not in our scheduling class.
 */
//used in following dequeue_task_wrr, put_prev_task_wrr, task_tick_wrr
static void update_curr_wrr(struct rq *rq)
{
	struct task_struct *curr = rq->curr;
	u64 delta_exec;

	if (curr->sched_class != &wrr_sched_class)
		return;

	delta_exec = rq->clock_task - curr->se.exec_start;
	if (unlikely((s64)delta_exec < 0))
		delta_exec = 0;

	schedstat_set(curr->se.statistics.exec_max, max(curr->se.statistics.exec_max, delta_exec));

	curr->se.sum_exec_runtime += delta_exec;
	account_group_exec_runtime(curr, delta_exec);

	curr->se.exec_start = rq->clock_task;
	cpuacct_charge(curr, delta_exec);
}

static struct task_struct *_pick_next_task_wrr(struct rq *rq)
{
	struct sched_wrr_entity *wrr_se;
	struct task_struct *p;
	struct wrr_rq *wrr_rq;

	wrr_rq = &rq->wrr;

	if (!wrr_rq->nr_wrr_running)
		return NULL;

	wrr_se = list_first_entry(&((rq->wrr)).queue, struct sched_wrr_entity, run_list);

	p = container_of(wrr_se, struct task_struct, wrr);

	return p;
}

static void enqueue_wrr_entity(struct rq *rq, struct sched_wrr_entity *wrr_se, bool head)
{
	struct list_head *queue = &(rq->wrr.queue);
	struct task_struct *p;

    	p = container_of(wrr_se, struct task_struct, wrr);
    	//printk("Enqueuing process: %d\n", p->pid);
	
	struct task_group *tg = task_group(p);//translate the type
    	char group_path[1024];
    	if (!(autogroup_path(tg, group_path, 1024)))
   	{
    		if (!tg->css.cgroup) {
        	    group_path[0] = '\0';
    	    	}
        	cgroup_path(tg->css.cgroup, group_path, 1024);
    	}

    	if(group_path[1] == 'b' && p->wrr.value != 0)
    	{
        	p->wrr.time_slice = WRR_BACKGROUND_TIMESLICE;
        	p->wrr.value = 0;
        	printk("Change timeslice to background\n");
    	}
    	else if(group_path[1] != 'b' && p->wrr.value != 1)
    	{
        	p->wrr.time_slice = WRR_FOREGROUND_TIMESLICE;
        	p->wrr.value = 1;
        	printk("Change timeslice to foreground\n");
    	}

    	if(head)
        	list_add(&wrr_se->run_list, queue);
    	else
        	list_add_tail(&wrr_se->run_list, queue);
    
    	rq->wrr.total_value += wrr_se->value;
    	++rq->wrr.nr_wrr_running;
}

static void dequeue_wrr_entity(struct rq *rq, struct sched_wrr_entity *wrr_se)
{
	struct task_struct *p;

    	p = container_of(wrr_se, struct task_struct, wrr);
    	//printk("Dequeuing process: %d\n", p->pid);

    	list_del_init(&wrr_se->run_list);
    	rq->wrr.total_value -= wrr_se->value;
    	--rq->wrr.nr_wrr_running;
}

/*
 * Adding/removing a task to/from a priority array:
 */
static void enqueue_task_wrr(struct rq *rq, struct task_struct *p, int flags)
{
	struct sched_wrr_entity *wrr_se = &p->wrr;

	enqueue_wrr_entity(rq, wrr_se, flags & ENQUEUE_HEAD);
	inc_nr_running(rq);
}

static void dequeue_task_wrr(struct rq *rq, struct task_struct *p, int flags)
{
	struct sched_wrr_entity *wrr_se = &p->wrr;

	update_curr_wrr(rq);//update data in the queue	
	dequeue_wrr_entity(rq, wrr_se);
	dec_nr_running(rq);
}

/*
 * Put task to the head or the end of the run list without the overhead of
 * dequeue followed by enqueue.
 */
static void requeue_task_wrr(struct rq *rq, struct task_struct *p, int head)
{
    	//printk("Requeuing task: %d\n", p->pid);

    	struct list_head *queue = &(rq->wrr.queue);
	struct sched_wrr_entity *wrr_se = &p->wrr;
    

    	if (head)
        	list_move(&wrr_se->run_list, queue);
    	else
        	list_move_tail(&wrr_se->run_list, queue);
}

static void yield_task_wrr(struct rq *rq)
{
    requeue_task_wrr(rq, rq->curr, 0);
}

/*
 * for we didn't define prio in WRR, we needn't impl it
 */
static void check_preempt_curr_wrr(struct rq *rq, struct task_struct *p, int flags)
{
}

static struct task_struct *pick_next_task_wrr(struct rq *rq)
{
	struct sched_wrr_entity *wrr_se;
	struct task_struct *p;
	
	if(!(rq->wrr.nr_wrr_running))
		return NULL;
	
	wrr_se = list_first_entry(&(rq->wrr).queue, struct sched_wrr_entity, run_list);	
	p = container_of(wrr_se, struct task_struct, wrr);
	return p;
}

static void put_prev_task_wrr(struct rq *rq, struct task_struct *p)
{
	update_curr_wrr(rq);

	/*
	 * The previous task needs to be made eligible for pushing
	 * if it is still active
	 */
	p->se.exec_start = 0;
}

void init_wrr_rq(struct wrr_rq *wrr_rq, struct rq *rq)
{
    
    INIT_LIST_HEAD(&wrr_rq->queue);
    wrr_rq->nr_wrr_running = 0;
    wrr_rq->total_value = 0;
}

//functions never need impl
#ifdef CONFIG_SMP

static int
select_task_rq_wrr(struct task_struct *p, int sd_flag, int flags)
{
}

#endif /*COMFIG_SMP*/

#ifdef CONFIG_SMP
static void set_cpus_allowed_wrr(struct task_struct *p, const struct cpumask *new_mask)
{
}
static void rq_online_wrr(struct rq *rq)
{
}
static void rq_offline_wrr(struct rq *rq)
{
}
static void pre_schedule_wrr(struct rq *rq, struct task_struct *prev)
{
}
static void post_schedule_wrr(struct rq *rq)
{
}
static void task_woken_wrr(struct rq *rq, struct task_struct *p)
{
}
static void switched_from_wrr(struct rq *rq, struct task_struct *p)
{
}
#endif

static void set_curr_task_wrr(struct rq *rq)
{
	struct task_struct *p = rq->curr;

	p->se.exec_start = rq->clock_task;

}

//used for set runtime, print info
static void task_tick_wrr(struct rq *rq, struct task_struct *p, int queued)
{
	struct sched_wrr_entity *wrr_se = &p->wrr;
	update_curr_wrr(rq);

	struct task_group *tg = p->sched_task_group;
    	char group_path[1024];
    	if (!(autogroup_path(tg, group_path, 1024)))
    	{
        	if (!tg->css.cgroup) {
         		group_path[0] = '\0';
        	}
        	cgroup_path(tg->css.cgroup, group_path, 1024);
    	}

    	printk("In task_tick_wrr: task_group: %s\n", group_path);
    	printk("  task_tick: %d time_slice: %d\n", p->pid, p->wrr.time_slice);

	if (--p->wrr.time_slice)
		return;

	if(p->wrr.value == 1)
		p->wrr.time_slice = WRR_FOREGROUND_TIMESLICE;
	else
		p->wrr.time_slice = WRR_BACKGROUND_TIMESLICE;

	if (wrr_se->run_list.prev != wrr_se->run_list.next) {
		requeue_task_wrr(rq, p, 0);
		resched_task(p);
		return;
	}
}
//get info about this task is Background or Foreground according to length of timeslice
static unsigned int get_rr_interval_wrr(struct rq *rq, struct task_struct *task)
{
	struct task_group *tg = task->sched_task_group;
    	char group_path[1024];
    	if (!(autogroup_path(tg, group_path, 1024)))
    	{
        	if (!tg->css.cgroup) {
         		group_path[0] = '\0';
        	}
        	cgroup_path(tg->css.cgroup, group_path, 1024);
    	}
	 printk("get_wrr_interval_Task_group: %s\n", group_path);
    if(group_path[1]=='\0')
        return WRR_FOREGROUND_TIMESLICE;
    else
        return WRR_BACKGROUND_TIMESLICE;	
}

static void
prio_changed_wrr(struct rq *rq, struct task_struct *p, int oldprio)
{
}

static void switched_to_wrr(struct rq *rq, struct task_struct *p)
{
}

#ifdef CONFIG_WRR_GROUP_SCHED

#endif


const struct sched_class wrr_sched_class = {
	.next 			= &fair_sched_class,		/*Required*/
	.enqueue_task  		= enqueue_task_wrr,		/*Required*/
	.dequeue_task 		= dequeue_task_wrr,		/*Required*/
	.yield_task 		= yield_task_wrr,		/*Required*/
	.check_preempt_curr 	= check_preempt_curr_wrr,	/*Required*/
	
	.pick_next_task 	= pick_next_task_wrr,		/*Required*/
	.put_prev_task 		= put_prev_task_wrr,		/*Required*/
	
	//.task_fork 		= task_fork_wrr,	
#ifdef CONFIG_SMP
	.select_task_rq 	= select_task_rq_wrr,	/*Never need impl*/
	.set_cpus_allowed 	= set_cpus_allowed_wrr,
	.rq_online 		= rq_online_wrr,	/*Never need impl*/
	.rq_offline 		= rq_offline_wrr,	/*Never need impl*/
	.pre_schedule 		= pre_schedule_wrr,	/*Never need impl*/
	.post_schedule 		= post_schedule_wrr,	/*Never need impl*/
	.task_woken 		= task_woken_wrr,	/*Never need impl*/
	.switched_from 		= switched_from_wrr,	/*Never need impl*/
#endif
	
	.set_curr_task 		= set_curr_task_wrr,	/*Required*/
	.task_tick 		= task_tick_wrr,	/*Required*/
	
	.get_rr_interval 	= get_rr_interval_wrr,
	
	.prio_changed 		= prio_changed_wrr,	/*Never need impl*/
	.switched_to 		= switched_to_wrr,	/*Never need impl*/
};

#ifdef CONSIG_SMP

#endif
