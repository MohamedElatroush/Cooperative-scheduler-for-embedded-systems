# Cooperative-scheduler-for-embedded-systems

## The scheduler Logic:
There is a struct named "Task" which contains the task pinter, priority and sleep time. The scheduler has 2 Tasks queues; the ready and the delay. The tasks in the ready queue are sorted based on their priorities, when a dispatch is called, the task in the front of the queue will be popped and executed. The delay queue holds the tasks that still are still sleeping, and sorts them based on their sleeping time. After each clock tick the sleeping time decrements to all tasks in the DelayQueue, once one of these tasks have sleepingTime = 0, it'll be transfered from the delay queue to the ready queue.  

## The scheduler functions:
* **sched_init():** 
  * Which initializes both queues (delayed and ready)
* **QueueTask(void(*)(void), int):** 
  * Takes the pointer to the task and its priority
  * Checks first that the priority level is valid from 1-7 else it will exit and print an error
  * If the priority level is valid, it enqueues the task to the readyQueue and sorts it based on the task priority; the task with the highest priority (lowest integer value) will be in the front of the queue
* **QueDelayedTask(void(*) (void), int, int):**
  * Takes the pointer to the task, its priority and the sleep time
  * This function enqueues the task to the delayQueue and sorts the queue based on the sleep time, the task with the least sleep time remaining will be in the front of the queue.   
* **ReRunMe(void(*)(void), int, int):** 
  * Takes the pointer to the task, its priority and the sleep time
  * If the sleep time is zero, it adds the task to the ready queue automatically using the QueueTask function.
  * If the sleep time is greater than zero, it will add the task to the delayed queue using the QueDelayedTask function
* **Decrement_DelayedQueue():** 
  * This function is called after each clock tick in the infinite loop in the main
  * Is responsible for decrementing the sleepTime of all the tasks in the DelayQueue
  * Checks if the sleepTime of a task reaches 0, it'll remove this task from the DelayQueue and enqueues it to the ReadyQueue
* **Dispatch():**
  * It is called in the infinite loop in the main
  * This function pops the front task in the ReadyQueue and executes it
  * If the readyQueue is empty it will do nothing

## How to use the scheduler:
* The scheduler only supports tasks that have 0 arguments and returns nothing. It also suppports priority levels from 1-8.
* First initialize the scheduler using sched_init in the main
* After defining the tasks, use the function QueueTask to add all your tasks to the scheduler
* In the infinite loop in the main make sure to call the dispatch function along with the Decrement_DelayQueue function for the scheduler to work correctly
* If you wish for a certain task to be rerun after it finishes executing make sure to call the ReRunMe function in your task definition
* The main.c in this repo has all the functions' definitions along with an example of how to create and schedule 3 tasks with different priorities and rerunning times
* There is also a "Unit Tests" folder containing several different scenarios of the tasks and what is the output of the scheduler
* For simulation purposes all the tasks print their name to the UART to be displayed on the Renode simulation, however these tasks could be used to do anything else.
