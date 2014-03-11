#include"data.h"


struct TASK_SET getTaskSet(void)	//used to input a taskSet
{
struct TASK_SET taskset;
int i;
printf("=============================================================================================\n");
	printf("Enter the total no of tasks for this task_set --> ");
	scanf("%d",&taskset.total_tasks);

		if(!taskset.total_tasks)
		return taskset;
	printf("Enter the fixed priorities of the tasks...you can enter space seperated values too --> ");

	for(i=0;i<taskset.total_tasks;i++)
	{
		scanf("%d",&taskset.task[i].priority);
		taskset.task[i].priority=MAX_PRIORITY-taskset.task[i].priority;
	}

	for(i=0;i<taskset.total_tasks;i++)
	{
		taskset.task[i].id=i;

		printf("Enter the WCET of task %d --> ",i);
		scanf("%f",&taskset.task[i].WCET);

		printf("Enter the deadline of task %d --> ",i);
		scanf("%f",&taskset.task[i].deadline);

		printf("Enter the period of task %d --> ",i);
		scanf("%d",&taskset.task[i].period);

		taskset.task[i].utilization=(1.0*taskset.task[i].WCET)/taskset.task[i].period;

	}
printf("=============================================================================================\n");
return taskset;
}

void display_taskset(struct TASK_SET taskset)	//used to display the task sets
{
int i;
	printf("************************* TASK SET ************************\n");

		printf("TOTAL_TASKS ==--> %d\n",taskset.total_tasks);

		for(i=0;i<taskset.total_tasks;i++)
		{
		printf("TASK ID %2d \t| Fixed Priority-->%2d | Deadline-->%9.3f ",taskset.task[i].id,(MAX_PRIORITY-taskset.task[i].priority),taskset.task[i].deadline);
		printf("| Period-->%5d | WCET-->%8.3f | Utilization-->%8.3f |\n",taskset.task[i].period,taskset.task[i].WCET,taskset.task[i].utilization);
		}

	printf("************************************************************\n\n");
}


