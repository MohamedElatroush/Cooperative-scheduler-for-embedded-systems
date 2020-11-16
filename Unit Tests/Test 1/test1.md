# Test 1: Using ReRunMe(0) 

Task A here is the task with the highest priority, and will use ReRunMe with 0 sleeping time. This will lead to the blocking of tasks B and C, since A will always have the priority to execute.

<br>
void TaskA(){<br>
	//
	static uint8_t A_msg[] = "Task A\n"; <br>
	sendUART(A_msg, sizeof(A_msg));<br>
	ReRunMe(&TaskA, 1, 0);  //Setting TaskA to ReRunMe(0)<br>
}
<br>
void TaskB(){
<br>
	static uint8_t B_msg[] = "Task B\n";<br>
	sendUART(B_msg, sizeof(B_msg));<br>
	ReRunMe(&TaskB, 2, 4); <br>
}
<br>
void TaskC(){<br>
	static uint8_t C_msg[] = "Task C\n";
	<br>
	sendUART(C_msg, sizeof(C_msg));
	<br>
	ReRunMe(&TaskC, 3, 2); 
	<br>
}


## Inside the main function:

  QueTask(&TaskA,1);
  <br>
QueTask(&TaskB,2);
<br>
QueTask(&TaskC,3);
<br>
