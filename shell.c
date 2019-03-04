/* 
 * Flow of the code:
 *	1. Accept the command as user input.
 *	2. Call fork to create a child process.
 *	3. Execute the command in the child process
 *		while the parent waits for the command 
 *		to complete.
 *	4. Return to Step 1.
 *
 * Error handling added:
 *	1. fork(): If the OS runs out of memory or reaches
 *		the max. allowed processes, a child process
 * 		will not be created and it'll return -1.
 * 	2. execvp(): It'll never return on a successful
 * 		invocation, but will return -1 if failed.
 *	3. malloc(): It can fail if the OS runs out of memory. The
 * 		code exits in such a scenario.
 */

#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<stdio.h>
#include<readline/readline.h>
#include<sys/wait.h>


/*
 * Parse the input string into an array
 * to execute execvp.
 */

char **get_input(char *input){
	char **command = malloc(8 *sizeof(char*));

	if (command == NULL){
		perror("malloc failed.");
		exit(1);
	}

	char *separator = " ";
	char *parsed;
	int index = 0;

	// Parse the input at the separator
	parsed = strtok(input, separator);
	while(parsed != NULL){
		command[index] = parsed;
		index++;

		parsed = strtok(NULL, separator);
	}

	command[index] = NULL;
	return command;
}

int cd(char *path){
	return chdir(path);
}

int main(){
	char **command;
	char *input;
	pid_t child_pid;
	int stat_loc;

	while(1){
		//input = readline("unixsh> ");
		input = readline("> ");
		command = get_input(input);

		/* Handle empty commands.*/
		if (!command[0]){
			free(input);
			free(command);
			continue;
		}

		if (strcmp(command[0], "cd") == 0){
			if (cd(command[1]) < 0){
				perror(command[1]);
			}

			/* Skip the fork.*/
			continue;
		}


		/* Fork the current process */
		child_pid = fork();

		if (child_pid < 0){
			perror("Fork failed.");
			exit(1);
		}
		
		if (child_pid == 0){
			/* Never returns if the call is successful */
			if (execvp(command[0], command) < 0){
				perror(command[0]);
				exit(1);
			}
		}
		else{
			waitpid(child_pid, &stat_loc, WUNTRACED);
		}

		/* Deallocate memory allotted to input and command */
		free(input);
		free(command);
	}

	return 0;
}
		
