# Attempting to input an invalid priority number
We're trying here to give TaskA an invalid priority number, to test the program since the schedueler supports 8 priority levels.
## Tasks Definition:
void TaskA(){
	//<br>
	static uint8_t A_msg[] = "Task A\n"; <br>
	sendUART(A_msg, sizeof(A_msg));<br>
	ReRunMe(&TaskA, 1, 6); <br>
}
<br>
void TaskB(){<br>
	static uint8_t B_msg[] = "Task B\n";<br>
	sendUART(B_msg, sizeof(B_msg));<br>
	ReRunMe(&TaskB, 2, 4); <br>
}
<br>
void TaskC(){<br>
	static uint8_t C_msg[] = "Task C\n";<br>
	sendUART(C_msg, sizeof(C_msg));<br>
	ReRunMe(&TaskC, 3, 2); <br>
}
<br>
## Priority 11 to TaskA (Invalid)
<br>
QueTask(&TaskA,11);<br>
QueTask(&TaskB,2);<br>
QueTask(&TaskC,3);<br>
