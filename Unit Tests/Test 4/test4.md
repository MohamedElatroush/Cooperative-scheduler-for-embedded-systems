# Test 4: Testing with 4 Tasks (A, B, C, D) - Scalability Test
void TaskA(){
	//
	static uint8_t A_msg[] = "Task A\n";
	sendUART(A_msg, sizeof(A_msg));
	ReRunMe(&TaskA, 5, 5); 
}

void TaskB(){
	static uint8_t B_msg[] = "Task B\n";
	sendUART(B_msg, sizeof(B_msg));
	ReRunMe(&TaskB, 1, 10); 
}

void TaskC(){
	static uint8_t C_msg[] = "Task C\n";
	sendUART(C_msg, sizeof(C_msg));
	ReRunMe(&TaskC, 3, 3); 
}

void TaskD(){
	static uint8_t D_msg[] = "Task D\n";
	sendUART(D_msg, sizeof(D_msg));
	ReRunMe(&TaskD, 8, 4); 
}

## Inside the main function
QueTask(&TaskA,5);
QueTask(&TaskB,1);
QueTask(&TaskC,3);
QueTask(&TaskD,8);
