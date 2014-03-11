#include"data.h"

int effective_utilization(struct TASK_SET,int);

int FP_Analysis(struct TASK_SET t,int REPORTING)
{
int i;
float sum=0.0;
float WRT=0.0;		//Worst Case Response Time
int FAILED_RT=0;	//This flag is set if the response time analysis fails

	if(REPORTING==REPORT_ON)
	printf(PRINT_MESSAGE("FIXED PRIORITY"));

	if(basic_schedulability_test(t)==-U_GREATER_1)
	{
		if(REPORTING==REPORT_ON)
		{
		printf("Satisfaction of necessary condition 	 : [%s]\n",FAILED);
		printf("Schedulability				 : [%s]\n",NOT_SCHEDULABLE);
		}
	return -U_GREATER_1;
	}
		
	for(i=0;i<t.total_tasks;i++)
	{
		if(effective_utilization(t,i)==SUCCESS)
		{
			if(REPORTING==REPORT_ON)
			printf("Task %d UB TEST		\t  : [%s]\n",t.task[i].id,PASSED);
		}
		else
		{
			if(REPORTING==REPORT_ON)
			printf("Task %d UB TEST		:[%s]\n",t.task[i].id,FAILED);

				if((WRT=RT_Test(i,t))>0.0)
				{
					if(REPORTING==REPORT_ON)
					{
					printf("RT_Test Task %d		: [%s]\n",t.task[i].id,PASSED);
					printf("WRT(%d)		   	: %f\n",t.task[i].id,WRT);
					}
				}
				else
				{
					if(REPORTING==REPORT_ON)
					printf("RT_Test Task %d		: [%s]\n",t.task[i].id,FAILED);
				FAILED_RT=1;	//we simply set the flag since we want to pinpoint exactly which tasks fail
				}		//At this point unschedulability is confirmed. For efficiency you 
						//may want to directly return
		}

	}

			if(!FAILED_RT)
			{
				if(REPORTING==REPORT_ON)
				{
				printf("Response Time Analysis	          : [%s]\n",PASSED);
				printf("Schedulability (RM/DM)            : [%s]\n",SCHEDULABLE);
				}

			return SUCCESS;
			}
			else	
			{
				if(REPORTING==REPORT_ON)
				{
				printf("Response Time Analysis	          : [%s]\n",FAILED);
				printf("Schedulability (RM/DM)            : [%s]\n",NOT_SCHEDULABLE);
				}

			return -FAILURE;
			}
}

int effective_utilization(struct TASK_SET t,int task)	//get effective utilization given by f formula in slides
{							
int i;
int Hn=0;
int H1=0;
int N;
float Hn_sum=0.0;
float H1_sum=0.0;
float utilization=0.0;
	
		for(i=0;i<task;i++)
		{	
			if(t.task[i].period<=t.task[task].deadline)
			{
			Hn_sum+=(t.task[i].WCET/(MINIMUM(t.task[i].deadline,t.task[i].period)));
			Hn++;
			}
			else
			H1_sum+=t.task[i].WCET;
		}

	N=Hn+1;	//U(n)=num(Hn)+1

	utilization=Hn_sum+(t.task[task].WCET/(MINIMUM(t.task[task].deadline,t.task[task].period)))+(H1_sum/(MINIMUM(t.task[task].deadline,t.task[task].period)));

float root=1.0/N;
float utilization_bound=N*(pow(2.0,root)-1);	//the sufficient condition for the utilization

//	printf("\nFor task %d\n",task);	
//	printf("N=%d\n",N);
//	printf("Utilization=%f\n",utilization);
//	printf("Utilization bound=%f\n",utilization_bound);

		if(utilization>utilization_bound)	//We fail the sufficient condition
		return -FAILURE;

return SUCCESS;
		
}
