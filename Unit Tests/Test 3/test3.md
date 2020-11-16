# Attempting to input an invalid priority number

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

## Priority 11 to TaskA (Invalid)
<br>
QueTask(&TaskA,11);
QueTask(&TaskB,2);
QueTask(&TaskC,3);
