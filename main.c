
#include "schedueler.c"

void TaskA(void);
void TaskB(void);

void TaskA(){
	//
	printf("TASK A\n");
	
}

void TaskB(){
	//
}


int main()
{
	init();
	QueTask(&TaskA,2);
	Dispatch();

	while(1)
	{
		
	}
}
