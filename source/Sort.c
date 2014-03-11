#include"data.h"

void swap(struct TASK *,struct TASK *);	//Function prototype that is private to this file

/********************************************************************************
Note: Different functions have been created in order to speed up the functions.
All could be combined into one function with a switch case loop but this
would cause an additional n^2 comparisons which is much more costlier than 
the extra lines of code!!
*********************************************************************************/

void sort_highest_priority(struct TASK_SET *t)	
{
int i,j;
struct TASK temp;

	for(i=0;i<t->total_tasks-1;i++)	
	for(j=i+1;j<t->total_tasks;j++)
	{
		if(t->task[j].priority>t->task[i].priority)	//DESCENDING ORDER
		{
			swap(&t->task[i],&t->task[j]);
		}
	}

}

void sort_deadline_monotonic(struct TASK_SET *t)
{
int i,j;
struct TASK temp;

	for(i=0;i<t->total_tasks-1;i++)	
	for(j=i+1;j<t->total_tasks;j++)
	{
		if((MINIMUM(t->task[j].deadline,t->task[j].period))<(MINIMUM(t->task[i].deadline,t->task[i].period)))	//ASCENDING ORDER
		{
		swap(&t->task[i],&t->task[j]);	//Note: The paratheses in the MACROS are absolutely necessary
		}				//else when expanded associativity will ensure inaccurate results
		
	}

}

void sort_rate_monotonic(struct TASK_SET *t)
{
int i,j;
struct TASK temp;

	for(i=0;i<t->total_tasks-1;i++)	
	for(j=i+1;j<t->total_tasks;j++)
	{
		if(t->task[j].period<t->task[i].period)	//ASCENDING ORDER
		swap(&t->task[i],&t->task[j]);
	}
}

void sort_edf(struct TASK_SET *t)
{
int i,j;
struct TASK temp;

	for(i=0;i<t->total_tasks-1;i++)	
	for(j=i+1;j<t->total_tasks;j++)
	{
		if(t->task[j].deadline<t->task[i].deadline)	//ASCENDING ORDER
		swap(&t->task[i],&t->task[j]);
	}
}

void swap(struct TASK *a,struct TASK *b)
{
struct TASK temp;

	temp=*a;
	*a=*b;
	*b=temp;
}
