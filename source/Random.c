/*-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x

									REAL TIME SYSTEMS
							      		RUSHANG V KARIA
									ASU # 1206337661
									ASSIGNMENT 2

This program was developed on the lab computer with a resolution of 1360x767.
Please make sure that you view the code in only this or a greater resolution for convenient viewing.

-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x*/

#include"data.h"
#include<stdlib.h>

#define MAX_SAMPLES 10000
#define M 3

enum { EDF, RM, DM };
const char *ALGORITHM[]={"EDF","RM","DM"};
/////////////////////////////////////////////
void reinitialize(float[]);
void UUniSort(int,float,float[]);
void UUniFast(int,float,float[]);
void sort(float[],int);
////////////////////////////////////////////


//---------------
FILE *file;
//--------------
void randomTaskSet(int MAX_TASK,int D_BETWEEN_C_T)
{

char *FILE_NAME=malloc(sizeof(char)*MAX_MEMORY);

srand(time(NULL));
int i;
struct TASK_SET t;
float U_BAR=0.05;
float utilization[MAX_TASK];
int EDF_SUCCESSFUL=0;
int RM_SUCCESSFUL=0;
int DM_SUCCESSFUL=0;
int SAMPLE=0;
int STATUS;
float DEADLINE_UPPER_BOUND;
float DEADLINE_LOWER_BOUND;
	
	sprintf(FILE_NAME,"%s_%d_%d","TASKSET",MAX_TASK,D_BETWEEN_C_T);
	file=fopen(FILE_NAME,"w");

	

		if(file==NULL)// || FILE_RM==NULL || FILE_DM==NULL)
		{
			printf("Error opening file...Exiting\n");
			return;
		}

fprintf(file,"U\tEDF\tDM\tRM\n");

if(D_BETWEEN_C_T)
printf("\t\t\tRANDOM ANALYSIS FOR %d TASKS PER TASKSET and deadlines between [C+(T-C)/2,T]\n",MAX_TASK);
else
printf("\t\t\tRANDOM ANALYSIS FOR %d TASKS PER TASKSET and deadlines between [C,T]\n",MAX_TASK);

while(U_BAR<=1)
{
printf("Generating and Testing for U_BAR=%f\n",U_BAR);

	while(SAMPLE++<MAX_SAMPLES)
	{
	//printf("-------------> Generating Random Task Sets <------------\n");
	t.total_tasks=MAX_TASK;//(int)rand()%(MAX_TASK-MIN_TASK)+MIN_TASK;

		for(i=0;i<t.total_tasks;i++)
		{
			t.task[i].id=i;			

			if(i<=t.total_tasks/3.0)
			t.task[i].period=rand()/(RAND_MAX*1.0)*(100-10)+10;
			else if(i>t.total_tasks/3.0 && i<(2.0/3.0)*t.total_tasks)
			t.task[i].period=rand()/(RAND_MAX*1.0)*(1000-100)+100;
			else
			t.task[i].period=rand()/(RAND_MAX*1.0)*(10000-1000)+1000;

			//t.task[i].priority=rand()%MAX_PRIORITY;	//its good to initialize priority even if we do not use them 
			
		}

//		UUniSort(t.total_tasks,U_BAR,utilization);
		UUniFast(t.total_tasks,U_BAR,utilization);

		for(i=0;i<t.total_tasks;i++)
		{
		t.task[i].utilization=utilization[i];
		t.task[i].WCET=utilization[i]*t.task[i].period;
		
		DEADLINE_UPPER_BOUND=t.task[i].period*1.0;
		DEADLINE_LOWER_BOUND=t.task[i].WCET+(D_BETWEEN_C_T*((t.task[i].period-t.task[i].WCET)/2.0));
		t.task[i].deadline=rand()/(RAND_MAX*1.0)*(DEADLINE_UPPER_BOUND-DEADLINE_LOWER_BOUND)+DEADLINE_LOWER_BOUND;
		}



	sort_edf(&t);
	STATUS=EDF_Analysis(t,REPORT_OFF);
	EDF_SUCCESSFUL+=((STATUS==SUCCESS)?1:0);
	//display_taskset(t);

	sort_rate_monotonic(&t);
	STATUS=RM_Analysis(t,REPORT_OFF,"RM");
	RM_SUCCESSFUL+=((STATUS==SUCCESS)?1:0);
	//display_taskset(t);

	sort_deadline_monotonic(&t);
	STATUS=RM_Analysis(t,REPORT_OFF,"RM");
	DM_SUCCESSFUL+=((STATUS==SUCCESS)?1:0);
	//display_taskset(t);


	}

//	printf("%% Scheduled by EDF are %f\n",(1.0*EDF_SUCCESSFUL)/MAX_SAMPLES);
//	printf("%% Scheduled by RM are %f\n",(1.0*RM_SUCCESSFUL)/MAX_SAMPLES);
//	printf("%% Scheduled by DM are %f\n",(1.0*DM_SUCCESSFUL)/MAX_SAMPLES);
//

	fprintf(file,"%f\t%f\t%f\t%f\n",U_BAR,(1.0*EDF_SUCCESSFUL)/MAX_SAMPLES,(1.0*DM_SUCCESSFUL)/MAX_SAMPLES,(1.0*RM_SUCCESSFUL)/MAX_SAMPLES);

EDF_SUCCESSFUL=0;
RM_SUCCESSFUL=0;
DM_SUCCESSFUL=0;
SAMPLE=0;
U_BAR+=0.1;
}//end of while(U_BAR)

fclose(file);


}//end of randomTaskSet()

void UUniFast(int total_tasks,float u_bar,float utilization[])
{
int i;

float sumU=u_bar;
float nextSumU;

			
	for(i=0;i<total_tasks-1;i++)
	{
		nextSumU=sumU*pow((rand()/(RAND_MAX*1.0)),(1.0/(total_tasks-i)));
		utilization[i]=sumU-nextSumU;
		sumU=nextSumU;
	}	

	utilization[total_tasks-1]=sumU;

/*
float sum=0.0;
		for(i=0;i<total_tasks;i++)	//This is the testing logic that makes sure that all utilizations generated are within
		sum+=utilization[i];		//U_BAR. Else it is inaccurate and inconclusive
						//ie the sum should be U_BAR
		printf("\nSum is%f\n ",sum);
*/
}

void UUniSort(int total_tasks,float u_bar,float utilization[])
{
int i;

float U[total_tasks+1];	//we need another array so that we can then subtract the adjacent values without changing the array
			//Please see the documentation of UUniSort
	U[0]=0.0;
	U[total_tasks]=u_bar;	

	for(i=1;i<total_tasks;i++)
	U[i]=rand()/(RAND_MAX*1.0)*u_bar;

	sort(U,(total_tasks+1));

		for(i=0;i<total_tasks;i++)
		utilization[i]=U[i+1]-U[i];		


/*	
float sum=0.0;
		for(i=0;i<total_tasks;i++)	//This is the testing logic that makes sure that all utilizations generated are within
		sum+=utilization[i];		//U_BAR. Else it is inaccurate and inconclusive
						//ie the sum should be U_BAR
		printf("\nSum is%f\n ",sum);
*/
}

void sort(float utilization[],int total_tasks)	
{
float temp;
int i,j;

	for(i=0;i<total_tasks-1;i++)
	{
		for(j=i+1;j<total_tasks;j++)
		{
			if(utilization[j]<utilization[i])	//ASCENDING ORDER
			{
			temp=utilization[i];
			utilization[i]=utilization[j];
			utilization[j]=temp;
			}
		}
	}
}

