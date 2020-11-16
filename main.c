#include "stm32f4xx.h"
#include "system_stm32f4xx.h"
#include <stdio.h>
#include <stdlib.h>


#define MAX_SIZE (100)


static int timer_counter = 0;
//static uint8_t pressedMsg[] = "Button is pressed !!\n";
//static uint8_t releasedMsg[] = "Button is released !!\n";
//static char buttonPressed = 1;
static char timerFlag = 0;
//static volatile uint8_t stopFlag = 0;

void TaskA(void);
void TaskB(void);
void TaskC(void);
void sched_init(void);
void QueTask(void(*)(void), int);
void ReRunMe(void(*)(void), int, int);
void Decrement_DelayedQueue(void);
void QueDelayedTask(void(*) (void), int, int);
void Dispatch(void);
void SysTick_Handler(void);
//void USART2_IRQHandler(void);
//void EXTI0_IRQHandler(void);
static void sendUART(uint8_t * data, uint32_t length);
//static uint8_t receiveUART(void);
static uint8_t failed[] = "ERROR!! - choose a priority number between 1 and 8\n";

void SysTick_Handler(void)  {
	timerFlag = 1;
}

//void USART2_IRQHandler(void) {
	/* pause/resume UART messages */
	//stopFlag = !stopFlag;
	
	/* dummy read */
	//(void)receiveUART();
//}

//void EXTI0_IRQHandler(void) {
		/* Clear interrupt request */
//		EXTI->PR |= 0x01;
		/* send msg indicating button state */
//		if(buttonPressed)
//		{
//				sendUART(pressedMsg, sizeof(pressedMsg));
//				buttonPressed = 0;
//		}
//		else
//		{
//				sendUART(releasedMsg, sizeof(releasedMsg));
//				buttonPressed = 1;
//		}
//}

static void sendUART(uint8_t * data, uint32_t length)
{
	 for (uint32_t i=0; i<length; ++i){
      // add new data without messing up DR register
      uint32_t value = (USART2->DR & 0x00) | data[i];
		  // send data
			USART2->DR = value;
      // busy wait for transmit complete
      while(!(USART2->SR & (1 << 6)));
		  // delay
      for(uint32_t j=0; j<1000; ++j);
      }
}

//static uint8_t receiveUART()
//{
	  // extract data
//	  uint8_t data = USART2->DR & 0xFF;
	
//	  return data;
//}

static void uartInit()
{
	
    // enable USART2 clock, bit 17 on APB1ENR
    RCC->APB1ENR |= (1 << 17);
	
	  // USART2 TX enable, TE bit 3
    USART2->CR1 |= (1 << 3);

    // USART2 rx enable, RE bit 2
    USART2->CR1 |= (1 << 2);
	
	  // USART2 rx interrupt, RXNEIE bit 5
    USART2->CR1 |= (1 << 5);

    // baud rate = fCK / (8 * (2 - OVER8) * USARTDIV)
    //   for fCK = 16 Mhz, baud = 115200, OVER8 = 0
    //   USARTDIV = 16Mhz / 115200 / 16 = 8.6805
    // Fraction : 16*0.6805 = 11 (multiply fraction with 16)
    // Mantissa : 8
    // 12-bit mantissa and 4-bit fraction
    USART2->BRR |= (8 << 4);
    USART2->BRR |= 11;

    // enable usart2 - UE, bit 13
    USART2->CR1 |= (1 << 13);
}

/*
//static void gpioInit()
{	
    // enable GPIOA clock, bit 0 on AHB1ENR
    RCC->AHB1ENR |= (1 << 0);
    // set pin modes as alternate mode 7 (pins 2 and 3)
    // USART2 TX and RX pins are PA2 and PA3 respectively
    GPIOA->MODER &= ~(0xFU << 4); // Reset bits 4:5 for PA2 and 6:7 for PA3
    GPIOA->MODER |=  (0xAU << 4); // Set   bits 4:5 for PA2 and 6:7 for PA3 to alternate mode (10)
    // set pin modes as high speed
    GPIOA->OSPEEDR |= 0x000000A0; // Set pin 2/3 to high speed mode (0b10)
    // choose AF7 for USART2 in Alternate Function registers
    GPIOA->AFR[0] |= (0x7 << 8); // for pin A2
    GPIOA->AFR[0] |= (0x7 << 12); // for pin A3
}
*/

typedef struct TASK_ {
	int Task_id; //Unique TaskID
	void(*task_ptr)(void); // pointer to function
	int priority; // priority of a task
	int sleep_time;
}TASK;

static int ReadyQueueSize;
static int DelayQueueSize;
static int TaskId;


static TASK Ready_Queue[MAX_SIZE];
static TASK Delay_Queue[MAX_SIZE];


void QueTask(void(*task_ptr)(void), int priority)
{
	if(priority < 1 || priority >8)
	{
		sendUART((uint8_t*)failed, sizeof(failed));
		exit(1);
	}
	int i,j;
	for(i=0;i<ReadyQueueSize;i++) // loop over the ready queue
	{
		if(priority < Ready_Queue[i].priority) // if the priority of the new Task is greater than the current task
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
												.priority = priority,
												.sleep_time = 0};
												
    
	ReadyQueueSize++;
	TaskId++;
	
}

void QueDelayedTask(void(*task_ptr)(void), int priority, int sleepTime)
{
	
	int i,j;
	
	for(i=0;i<DelayQueueSize;i++) // loop over the ready queue
	{
		if(sleepTime < Delay_Queue[i].sleep_time) // if the priority of the new Task is greater than the current task
		{
			break;
		}
	}
	for(j=DelayQueueSize;j>i;j--)
	{
		Delay_Queue[j] = Delay_Queue[j-1];
	}
	
	Delay_Queue[i]=(TASK){.Task_id = TaskId,
											  .task_ptr = task_ptr,
												.priority = priority,
												.sleep_time = sleepTime};
												
	DelayQueueSize++;
}

void ReRunMe(void(*task_ptr)(void), int priority, int sleepTime)
{
	if (sleepTime == 0)
	{
		QueTask(task_ptr, priority);
	}
	else
	{
		QueDelayedTask(task_ptr, priority, sleepTime);
	}
}

void sched_init(void)
{
	ReadyQueueSize = 0;
	DelayQueueSize = 0;
	TaskId = 0;
}

void Decrement_DelayedQueue(void)
{
	for (int i=0; i<DelayQueueSize; i++)
	{
		Delay_Queue[i].sleep_time--;
		
		//check if any of the tasks are now ready to enter the ready queue
		if(Delay_Queue[i].sleep_time == 0) 
		{
			
			//enqueue readyqueue
			QueTask(Delay_Queue[i].task_ptr, Delay_Queue[i].priority);
			//dequeue delayqueue
			int j;
			for(j=i+1;j<DelayQueueSize;j++)
			{
					Delay_Queue[j-1] = Delay_Queue[j];
			}
			DelayQueueSize--;
			i--;
		}
	}
	

}

void Dispatch(void)
{
	
    if(ReadyQueueSize != 0)
    {
    (*Ready_Queue[0].task_ptr)();
    int i;
    for(i=1;i<ReadyQueueSize;i++)
    {
        Ready_Queue[i-1] = Ready_Queue[i];
    }

    ReadyQueueSize--;
    }
		else
		{
			char new_line[] = "\n";
			sendUART((uint8_t*)new_line, sizeof(new_line));
		}
}

void TaskA(){
	//
	static uint8_t A_msg[] = "Task A\n";
	sendUART(A_msg, sizeof(A_msg));
	ReRunMe(&TaskA, 1, 6); 
}

void TaskB(){
	static uint8_t B_msg[] = "Task B\n";
	sendUART(B_msg, sizeof(B_msg));
	ReRunMe(&TaskB, 2, 4); 
}

void TaskC(){
	static uint8_t C_msg[] = "Task C\n";
	sendUART(C_msg, sizeof(C_msg));
	ReRunMe(&TaskC, 3, 2); 
}


int main()
{
		sched_init();
	
	/* startup code initialization */
	  SystemInit();
	  SystemCoreClockUpdate();
	  /* intialize UART */
	 // gpioInit();
		/* intialize UART */
	  uartInit();
	  /* enable SysTick timer to interrupt system every second */
	  SysTick_Config(SystemCoreClock/10);
	
	  /* enable interrupt controller for USART2 external interrupt */
		//NVIC_EnableIRQ(USART2_IRQn);
		/* Unmask External interrupt 0 */
		//EXTI->IMR |= 0x0001;
	  /* Enable rising and falling edge triggering for External interrupt 0 */
		//EXTI->RTSR |= 0x0001;
		//EXTI->FTSR |= 0x0001;
	  /* enable interrupt controller for External interrupt 0 */
		//NVIC_EnableIRQ(EXTI0_IRQn);
	
	QueTask(&TaskA,11);
	QueTask(&TaskB,2);
	QueTask(&TaskC,3);
	
	while(1)
	 {
		 if(timerFlag)
				{
						char temp[20] = {0};
						sprintf(temp, "Time %d: ", timer_counter);
						sendUART((uint8_t*)temp, sizeof(temp));
					  Dispatch();
						Decrement_DelayedQueue();
						timer_counter++;
						timerFlag = 0;
				}
		 
	 }
}
