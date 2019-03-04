/*
 * To perform proper process determinism.
 * Using sleep to do this task isn't very
 * effective as there's no guarantee that
 * the process will finish within the 
 * specified time. Another issue would
 * be if the process finishes much earlier.
 * 
 * We use waitpid() system call. Takes the
 * following parameters:
 *	1. Process ID of the program which needs to wait.
 *	2. A variable which will be populated with info on how the process was terminated.
 *	3. Options flag, to customize behavior of waitpid.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(){
	pid_t child_pid;
	pid_t wait_result;
	int stat_loc;

	child_pid = fork();

	// Child process
	if (child_pid == 0){
		printf("#### Child ####\nCurrent PID: %d and Child PID: %d\n", getpid(), child_pid);
		sleep(1); 	// Sleep for 1 second
	}
	else{
		wait_result = waitpid(child_pid, &stat_loc, WUNTRACED);
		printf("#### Parent ####\nCurrent PID: %d and Child PID: %d\n", getpid(), child_pid);
	}

	return 0;

}
