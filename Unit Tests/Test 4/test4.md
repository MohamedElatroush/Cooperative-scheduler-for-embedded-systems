# Test 4: Testing with 4 Tasks (A, B, C, D) - Scalability Test

## Tasks Definition:
void TaskA(){ <br>
	static uint8_t A_msg[] = "Task A\n"; <br>
	sendUART(A_msg, sizeof(A_msg));<br>
	ReRunMe(&TaskA, 5, 5); <br>
}<br>

void TaskB(){<br>
	static uint8_t B_msg[] = "Task B\n";<br>
	sendUART(B_msg, sizeof(B_msg));<br>
	ReRunMe(&TaskB, 1, 10); <br>
}<br>

void TaskC(){<br>
	static uint8_t C_msg[] = "Task C\n";<br>
	sendUART(C_msg, sizeof(C_msg));<br>
	ReRunMe(&TaskC, 3, 3); <br>
}<br>

void TaskD(){<br>
	static uint8_t D_msg[] = "Task D\n";<br>
	sendUART(D_msg, sizeof(D_msg));<br>
	ReRunMe(&TaskD, 8, 4); <br>
}<br>

## Inside the main function:
QueTask(&TaskA,5);<br>
QueTask(&TaskB,1);<br>
QueTask(&TaskC,3);<br>
QueTask(&TaskD,8);<br>
