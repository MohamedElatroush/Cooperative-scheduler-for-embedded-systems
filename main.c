
#include "schedueler.c"

void TaskA(void);
void TaskB(void);

void TaskA(){
	//
	printf("TASK A\n");
	
}

void TaskB(){
	printf("TASK B\n");
}

void TaskC(){
	printf("TASK C\n");
}


int main()
{
	init();
	QueTask(&TaskA,2);
	QueTask(&TaskC,3);
	QueTask(&TaskB,1);
	
	Dispatch();
	
	// while(1)
	// {
		
	// }
}
