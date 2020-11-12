#include <stdio.h>
#include <stdlib.h>

#define priorityLow (8)
#define priorityHigh (0)
#define MAX_SIZE (10)

void init(void);
void enqueue(void(*)(void), int);
void dequeue(int*);

typedef struct TASK_ {
	int Task_id;
	void(*task_ptr)(void);
	int priority;
}TASK;


static int ReadyQueueSize = 10;
static int TaskId = 0;


static TASK Ready_Queue[MAX_SIZE];


void enqueue(void(*task_ptr)(void), int priority)
{
	for(int i=0;i<ReadyQueueSize;i++)
	{
		if(priority < Ready_Queue[i].priority)
		{
			break;
		}
	}
	
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
