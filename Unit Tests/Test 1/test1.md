This test is about the functionality of using ReRunMe(0) 

The expected output is that the task that issued that function will keep running resulting in blocking all other tasks.


void TaskA(){
	//
	static uint8_t A_msg[] = "Task A\n";
	sendUART(A_msg, sizeof(A_msg));
	ReRunMe(&TaskA, 1, 0);  //Setting TaskA to ReRunMe(0)
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


In the main function:

  QueTask(&TaskA,1);
	QueTask(&TaskB,2);
	QueTask(&TaskC,3);
