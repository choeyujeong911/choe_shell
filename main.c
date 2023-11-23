#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pwd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "mysh.h"

#define MAX 255
#define NUM_OF_CMDS 12

char cBuf[MAX], hBuf[MAX], uBuf[MAX], dBuf[MAX];

int main() {

	/* Declare Vars */
	void *command_line;	// Full command line
	pid_t pid;			// Process number
	char path[BUFSIZ];	// Now path
	char **commands = { "ls", "cd", "pwd", "cp", "mv", "rm", "mkdir", "rmdir", "touch", "cat", "grep", "echo", "ps", "kill", "chmod", "chown", "history", "man", "df", "du", "find", "diff" };	// List of my all commands
	
	/* Start shell */
	while(1) {
		char* wait_test;
		gets(cBuf);

		/* Update(Get) info to print in shell */
		gethostname(hBuf, MAX);	// Device host name
		getlogin_r(uBuf, MAX);	// Login user name
		getcwd(dBuf, MAX);		// Forcused path
		
		/* Initialize parts */
		char *command = NULL;	// ex) ls
		char **val = { ".", };		// ex) /bin
		char *opt = NULL;		// ex) -al
		int cmd_index = -1;		// ex) 0
		int j = 0;

		/* Put one command line to cBuf and copy to command_line */
		printf("%s%s@%s%s:%s%s%s$ ", PURPLE, hBuf, uBuf, WHITE, BLUE, dBuf, WHITE);
		command_line = fgets(cBuf, MAX, stdin);
		// When command writing finish
		if(cBuf[strlen(cBuf) - 1] == '\n') cBuf[strlen(cBuf) - 1] = '\0';
		command_line = cBuf;
		// Divide full command into command part, path part, and option part
		char *tmp = strtok(command_line, " ");
		while(tmp != NULL) {
			tmp = strtok(NULL, " ");
			for(int i = 0; i < NUM_OF_CMDS; i++) { 
				if(strstr(tmp, commands[i]) != NULL) command = tmp; 
			}
			if(strchr(tmp, '-') != NULL && strchr(tmp, '/') == NULL) opt = tmp;
			else { val[j] = tmp; j++; }
		}
		tmp = NULL;	// Delete tmp

		/* Excute command */
		if(strcmp(command, "switch") == 0) {	// When user wants to switch shell to bash
			execl("/bin/bash", "bash", (char*) NULL);
			perror("Exec Failed");
			exit(EXIT_FAILURE);
		}
		else {	// When command is implemented command
			pid = fork();
			if(pid < 0) { perror("Fork Failed"); exit(EXIT_FAILURE); }
			/* if-else execution */
			else if(pid == 0) { 
				switch(cmd_index) {
					case 0: _ls(val[0], opt); printf("case 0\n"); gets(wait_test); break;
					case 1: _cd(val[0]); printf("case 1\n"); gets(wait_test); break;
					default: printf("%sNo Such Command: %s%s\n", RED, command, WHITE); gets(wait_test);
				}
			}
			else waitpid(pid, NULL, 0);
			gets(wait_test);
		}
	}
	return 0;
}
