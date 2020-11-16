# Cooperative-scheduler-for-embedded-systems

The scheduler has 3 functions which the user shall use while coding his program:
*sched_init(): 
**Which initializes both queues (delayed and ready)
QueueTask(void(*)(void), int): 
Takes the pointer to the task and its priority
This function enqueues the task to the readyQueue and sorts it based on the functions priority; the function with the highest priority (lowest integer value) will be in the front of the queue
QueDelayedTask(void(*) (void), int, int):
Takes the pointer to the task, its priority and the sleep time
This function enqueues the task to the delayQueue and sorts the queue based on the sleep time, the function with the least sleep time remaining will be in the front of the queue.   
ReRunMe(void(*)(void), int, int): 
Takes the pointer to the task, its priority and the sleep time
If the sleep time is zero, it adds the task to the ready queue automatically using the QueueTask function.
If the sleep time is greater than zero, it will add the task to the delayed queue using the QueDelayedTask function
Decrement_DelayedQueue(): 


