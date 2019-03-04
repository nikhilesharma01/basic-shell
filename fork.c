/*
 * Basic shell workflow:
 *    1. Startup the shell
 *    2. Wait for user input
 *    3. Parse user input
 *    4. Execute the command and return the result
 *    5. Go back to 2
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    pid_t child_pid = fork();

    // Child process
    if (child_pid == 0)
        printf("#### child ####\nCurrent PID: %d and Child PID: %d\n", getpid(), child_pid);

    else
        printf("#### Parent ####\nCurrent PID: %d and Child PID: %d\n", getpid(), child_pid);

    return 0;

}
