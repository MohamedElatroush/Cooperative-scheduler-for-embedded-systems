# Test 1: Using ReRunMe(0) 

The expected output is that the task that issued that function will keep running resulting in blocking all other tasks.

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
