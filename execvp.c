/*
 * Execvp: vp indicates that it accepts
 * the name of a file, for which it
 * will search for in the PATH variable
 * of the system and an array of 
 * arguments to be executed.
 */

#include <unistd.h>

int main(){
	char *argv[] = {"ls", "-l", "-h", "-a", NULL};
	execvp(argv[0], argv);

	return 0;
}


