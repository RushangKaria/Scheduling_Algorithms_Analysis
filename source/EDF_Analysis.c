#include"data.h"
////////////////
int loading_factor_test(struct TASK_SET);
////////////////

int EDF_Analysis(struct TASK_SET t,int REPORTING)
{
float utilization=0;
int i;

	if(REPORTING==REPORT_ON)
	printf(PRINT_MESSAGE("EDF"));
	
	for(i=0;i<t.total_tasks;i++)	
	utilization+=t.task[i].WCET/(MINIMUM(t.task[i].deadline,t.task[i].period));//compute the utilization

		if(basic_schedulability_test(t)==-U_GREATER_1)
		{
			if(REPORTING==REPORT_ON)
			{
			printf("Satisfaction of necessary condition 	 : [%s]\n",FAILED);
			printf("Schedulability				 : [%s]\n",NOT_SCHEDULABLE);
			}

		return -U_GREATER_1;
		}
		else if(utilization<=1)
		{
			if(REPORTING==REPORT_ON)
			{
			printf("Total density		    	  : %f\n",utilization);
			printf("EDF Utilization test status 	  : [%s]\n",PASSED);
			printf("Schedulability (EDF)        	  : [%s]\n",SCHEDULABLE);
			}

		return SUCCESS;
		}
		else
		{
			if(REPORTING==REPORT_ON)
			{
			printf("Total density 	 	     : %f\n",utilization);
			printf("EDF Utilization test status  : [%s]\n",FAILED);
			printf("Schedulability (EDF)         : [%s]\n",NOT_SURE);
				printf("\t\t%s---------> Loading Factor Test <-----------%s\n",BOLD_BLACK,NORMAL);
			}

		int x= loading_factor_test(t);	//We failed sufficient condition..Time to do loading factor

			if(x==SUCCESS)	//Loading factor passes. Tasks are schedulable
			{
				if(REPORTING==REPORT_ON)
				{
				printf("Loading Factor Test	    : [%s]\n",PASSED);
				printf("Schedulability (EDF)        : [%s]\n",SCHEDULABLE);
				}

			return SUCCESS;
			}
			else	//Failure if loading factor. Tasks are unschedulable
			{	if(REPORTING==REPORT_ON)
				{
				printf("Loading Factor Test	    : [%s]\n",FAILED);
				printf("Schedulability (EDF)        : [%s]\n",NOT_SCHEDULABLE);
				}

			return -FAILURE;
			}
		}
}

int loading_factor_test(struct TASK_SET t)
{
float L[MAX_MEMORY]={0.0};
float set_of_points[MAX_MEMORY]={0.0};
int set_size=0;
int size=0;
int interval=0;
int BREAK=0;
int i;

	for(i=0;i<t.total_tasks;i++)
	L[0]+=t.task[i].WCET;
	
	do
	{
	size++;
		for(i=0;i<t.total_tasks;i++)
		{
		L[size]+=ceil(L[size-1]/t.task[i].period)*t.task[i].WCET;	
		//printf("%f %f %f \n",temp,ceil(temp),L[size]);
		}
	}
	while(L[size-1]!=L[size]);
		
	while(!BREAK)	//We get the points to be considered for the test
	{
		for(i=0;i<t.total_tasks;i++)
		if(t.task[i].deadline+(interval*t.task[i].period)<=L[size])	//if less than L add to points and increase arrival
		set_of_points[set_size++]=t.task[i].deadline+(interval*t.task[i].period);
		else
		{
		BREAK=1;
		break;
		}

	interval++;
	}
//	set_size--;	//for the extra hit that we get

//	for(i=0;i<set_size;i++)
//	printf("%f ",set_of_points[i]);

	float h[MAX_MEMORY]={0.0};
	int index=0;

			while(index<set_size)	//Computation of h...It is the same as that for set_of_points
			{			//but we add the execution time only.
				for(i=0;i<t.total_tasks;i++)
				{
					int time_interval=0;

						while(t.task[i].deadline+(time_interval*t.task[i].period)<=set_of_points[index])
						{
						h[index]+=t.task[i].WCET;
						time_interval++;
						}
				}

			index++;
			}

//	for(i=0;i<index;i++)
//	printf("%f ",h[i]);

		for(i=0;i<index;i++)	//if utilization > 1 return failure
		if(h[i]/set_of_points[i]>1)
		return FAILURE;
		

return SUCCESS;
	
}

int basic_schedulability_test(struct TASK_SET t)	//To check the necessary condition sum(e/p)<=1
{
float utilization=0;
int i;
	for(i=0;i<t.total_tasks;i++)	
	utilization+=(t.task[i].WCET/t.task[i].period);

	if(utilization>1)
	{
//	printf("Utilization is %f\n",utilization);
	return -U_GREATER_1;
	}
	else
	return SUCCESS;
}
