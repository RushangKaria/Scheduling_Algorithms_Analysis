#include"data.h"

int RM_Analysis(struct TASK_SET t,int REPORTING,const char *ALGORITHM)
{
int U(int,struct TASK_SET);

float root=1.0/t.total_tasks;
float utilization_bound=t.total_tasks*(pow(2.0,root)-1);
float utilization=0.0;
int i;
int FAILED_RT=0;
float WRT=0.0;
	
	if(REPORTING==REPORT_ON)
	printf(PRINT_MESSAGE(ALGORITHM));

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
		utilization+=(t.task[i].WCET/(MINIMUM(t.task[i].period,t.task[i].deadline)));	//Parentheses outside MACRO required

			if(utilization<=utilization_bound)
			{
				if(REPORTING==REPORT_ON)
				{
				printf("Max utilization 	  	  : %f\n",utilization_bound);
				printf("Total utilization 	  	  : %f\n",utilization);
				printf("RM/DM  Utilization test status    : [%s]\n",PASSED);
				printf("Schedulability (RM)         	  : [%s]\n",SCHEDULABLE);
				}

				return SUCCESS;
			}
			else
			{
				if(REPORTING==REPORT_ON)
				{
				printf("Max utilization 	  	  : %f\n",utilization_bound);
				printf("Total utilization 	  	  : %f\n",utilization);
				printf("RM/DM  Utilization test status 	  : [%s]\n",FAILED);
				printf("Schedulability (RM)         	  : [%s]\n",NOT_SURE);
				printf("\t\t%s---------> Response Time Analysis <-----------%s\n",BOLD_BLACK,NORMAL);
				}

					for(i=0;i<t.total_tasks;i++)
					{
						if(U(i,t)==SUCCESS)
						{
							if(REPORTING==REPORT_ON)
							printf("U(%d)		: [%s]\n",t.task[i].id,PASSED);
						}
						else
						{
							if(REPORTING==REPORT_ON)
							printf("U(%d)		: [%s]\n",t.task[i].id,FAILED);
							
							if((WRT=RT_Test(i,t))>0.0)
							{
								if(REPORTING==REPORT_ON)
								{
								printf("RT_Test Task %d	: [%s]\n",t.task[i].id,PASSED);
								printf("WRT(%d)		: %f\n",i,WRT);
								}
							}
							else
							{
								if(REPORTING==REPORT_ON)
								printf("RT_Test Task %d	: [%s]\n",t.task[i].id,FAILED);

							FAILED_RT=1;
							}
						}
					}
				if(!FAILED_RT)
				{
					if(REPORTING==REPORT_ON)
					{
					printf("Response Time Analysis	    : [%s]\n",PASSED);
					printf("Schedulability (RM/DM)      : [%s]\n",SCHEDULABLE);
					}

				return SUCCESS;
				}
				else	
				{
					if(REPORTING==REPORT_ON)
					{
					printf("Response Time Analysis	    : [%s]\n",FAILED);
					printf("Schedulability (RM/DM)      : [%s]\n",NOT_SCHEDULABLE);
					}

				return -FAILURE;
				}
			}
}

float RT_Test(int tasks,struct TASK_SET t)
{
float a[MAX_MEMORY]={0.0};
int i,j;
float ei=t.task[tasks].WCET;
float sum;

	for(i=0;i<(tasks+1);i++)
	a[0]+=t.task[i].WCET;

i=1;
		while(i<MAX_MEMORY)
		{
		sum=ei;

			for(j=0;j<tasks;j++)
			sum+=ceil(a[i-1]/t.task[j].period)*t.task[j].WCET;
		
		a[i]=sum;

			if(a[i]==a[i-1])
			break;
			
		i++;
		}

//	printf("Task deadline %f Task WRT %f",t.task[tasks].deadline,a[i]);

return a[i]<=t.task[tasks].deadline && i<MAX_MEMORY?a[i]:-FAILURE;
}

int U(int tasks,struct TASK_SET t)
{
float root=1.0/(tasks+1);
float utilization_bound=(tasks+1)*(pow(2.0,root)-1);	
float utilization=0.0;
int i;
	
		for(i=0;i<(tasks+1);i++)	
		utilization+=(t.task[i].WCET/(MINIMUM(t.task[i].period,t.task[i].deadline)));	//CHECK THIS...

	//printf("Bound and value is %f %f\n",utilization_bound,utilization);

return utilization<=utilization_bound?SUCCESS:-FAILURE;
}
