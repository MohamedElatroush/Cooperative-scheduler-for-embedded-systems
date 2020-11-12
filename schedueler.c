#include <stdio.h>
#include <stdlib.h>

#define priorityLow (8)
#define priorityHigh (0)
#define MAX_SIZE (10)

void init(void);
void QueTask(void(*)(void), int);
void Dispatch(void);

typedef struct TASK_ {
	int Task_id; //Unique TaskID
	void(*task_ptr)(void); // pointer to function
	int priority; // priority of a task
}TASK;


static int ReadyQueueSize;
static int TaskId;


static TASK Ready_Queue[MAX_SIZE];


void QueTask(void(*task_ptr)(void), int priority)
{
	int i,j;
	for(i=0;i<ReadyQueueSize;i++) // loop over the ready queue
	{
		if(priority > Ready_Queue[i].priority) // if the priority of the new Task is greater than the current task
		{
			break;
		}
	}
	for(j=ReadyQueueSize;j>i;j--)
	{
		Ready_Queue[j] = Ready_Queue[j-1];
	}
	
	Ready_Queue[i]=(TASK){.Task_id = TaskId,
											  .task_ptr = task_ptr,
												.priority = priority};
												
    
	ReadyQueueSize++;
	TaskId++;
	printf("here\n");
}




void init(void)
{
	ReadyQueueSize = 0;
	TaskId = 0;
	
	//Ready queue (Sorted based on the task priorities)
	
	//QueTask() inserts a task to the ready queue, pass a pointer to the function that implements the task and priority
	
	//Dispatch() removes the highest priority from the queue and run it 
	
	//ReRunMe() //0: Task will enqueue itself
	
}

void Dispatch(void)
{
	//(*Ready_Queue[0].task_ptr);
	(*Ready_Queue[0].task_ptr)();

	ReadyQueueSize--;
	//
}
