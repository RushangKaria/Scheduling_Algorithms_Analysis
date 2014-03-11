/*-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x

									REAL TIME SYSTEMS
							      		RUSHANG V KARIA
									ASU # 1206337661
									ASSIGNMENT 2

This program was developed on the lab computer with a resolution of 1360x767.
Please make sure that you view the code in only this or a greater resolution for convenient viewing.

For best viewing open in gedit 
Go to edit select preferences.
Enable line numbers

Go to font and colors
Select Oblivion

-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x*/

#include"data.h"

////////// GLOBAL VARIABLES ////////////
struct TASK_SET task_set[MAX_TASKSETS];	
int task_set_pointer=0;
////////////////////////////////////////

//=================================================================== FUNCTION BODY STARTS HERE ====================================================================

int main(void)
{
int i;

	while(1)
	{
		task_set[task_set_pointer]=getTaskSet();

	
			if(!task_set[task_set_pointer].total_tasks)
			break;

	task_set_pointer++;


	}

	for(i=0;i<task_set_pointer;i++)
	{
		printf("##############################################################################################\n");
		printf("Here is the task set for your reference\n");
		display_taskset(task_set[i]);	

		sort_edf(&task_set[i]);
		EDF_Analysis(task_set[i],REPORT_ON);
		
		sort_rate_monotonic(&task_set[i]);
		RM_Analysis(task_set[i],REPORT_ON,"RM");

		sort_deadline_monotonic(&task_set[i]);
		RM_Analysis(task_set[i],REPORT_ON,"DM");

		sort_highest_priority(&task_set[i]);
		FP_Analysis(task_set[i],REPORT_ON);
		printf("##############################################################################################\n");
	}


		printf(PRINT_MESSAGE("RANDOM ANALYSIS"));
		randomTaskSet(10,0);
		randomTaskSet(20,0);
		randomTaskSet(50,0);

		randomTaskSet(10,1);
		randomTaskSet(20,1);
		randomTaskSet(50,1);



return 0;
}



