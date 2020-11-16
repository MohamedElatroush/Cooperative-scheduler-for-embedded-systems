# Test 2: Scheduling of 3 Tasks

Task A has the highest priority then B then C. A reruns itself giving sleeping time of 6, B reruns itself giving sleeping time of 4 and C reruns itself giving sleeping time of 2. The expected output is the execution of A->B->C then the readyQueue will be empty for 1 tick then it will start executing C->B->A->C and so on.   

## Tasks Definition:
void TaskA(){  <br>
	static uint8_t A_msg[] = "Task A\n"; <br>
	sendUART(A_msg, sizeof(A_msg));  <br>
	ReRunMe(&TaskA, 1, 6);  <br>
}  <br>

void TaskB(){  <br>
	static uint8_t B_msg[] = "Task B\n";  <br>
	sendUART(B_msg, sizeof(B_msg));  <br>
	ReRunMe(&TaskB, 2, 4);   <br>
}  <br>

void TaskC(){  <br>
	static uint8_t C_msg[] = "Task C\n";  <br>
	sendUART(C_msg, sizeof(C_msg));  <br>
	ReRunMe(&TaskC, 3, 2);  <br>
}  <br>

## Inside the main function:
QueTask(&TaskA,1);  <br>
QueTask(&TaskB,2);  <br>
QueTask(&TaskC,3);  <br>
