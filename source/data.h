//-----------INCLUDES AND DEFINES-----------

#ifndef _DATA_ASSIGNMENT_1
#define _DATA_ASSIGNMENT_1

#include<stdio.h>
#include<math.h>

#define MAX_TASKS 1000		//The max no of tasks that can be there in a taskset
#define MAX_TASKSETS 1000	//The max no of tasksets that are possible	
#define MAX_MEMORY 1000		//The max memory available for intermediate operations like those in RT tests

#define MAX_PRIORITY 1000	//Transformation function since I use high numbers as high priorities

#define U_GREATER_1 1		//ERROR CODE (UTILIZATION>1)
#define SUCCESS 0		
#define FAILURE 2		//ERROR CODE (CANNOT BE SCHEDULED)	we differentiate between both so that in the future we may 
				//					easily extend functionality
#define REPORT_ON 1		//This turns on the printf statements
#define REPORT_OFF 0		
#define MINIMUM(A,B) A<B?A:B	//MACRO to get the minimum

#define NOT_SURE	"\e[1;34mNOT SURE\e[0m"
#define SCHEDULABLE	"\e[1;32mSCHEDULABLE\e[0m"	
#define NOT_SCHEDULABLE	"\e[1;31mNOT SCHEDULABLE\e[0m"
#define PASSED		"\e[1;35mPASSED\e[0m"
#define FAILED		"\e[1;30mFAILED\e[0m"


#define BOLD_BLACK 	"\e[1;28m"
#define NORMAL		"\e[0m"
#define PRINT_MESSAGE(A)	"%s------------------------ APPLYING %s ANALYSIS -------------------------%s\n",BOLD_BLACK,A,NORMAL
//------------------------------------------

/*
Following are the task structures of the program
*/

struct TASK
{
int id;			//Unique Id for this task
float deadline;
int period;
float WCET;		//Worst Case Execution Time
float utilization;	//we store utilization also, to prevent excessive computation again and again
int priority;		//ie compute once use many
};

struct TASK_SET
{
int total_tasks;
struct TASK task[MAX_TASKS];
};

///////////////////////////////////////////////////////////////
extern int basic_schedulability_test(struct TASK_SET);
extern int EDF_Analysis(struct TASK_SET,int);
extern int FP_Analysis(struct TASK_SET,int);
extern int RM_Analysis(struct TASK_SET,int,const char *);

extern float RT_Test(int,struct TASK_SET);

extern void display_taskset(struct TASK_SET);
extern void sort_highest_priority(struct TASK_SET *);
extern void sort_deadline_monotonic(struct TASK_SET *);
extern void sort_rate_monotonic(struct TASK_SET *);
extern void sort_edf(struct TASK_SET *);

extern void randomTaskSet(int,int);

extern struct TASK_SET getTaskSet(void);
extern void display_taskset(struct TASK_SET);
extern void setColor(int);
////////////////////////////////////////////////////////////////

#endif

