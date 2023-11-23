#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pwd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "mysh.h"

#define PURPLE "\033[0;35m" 
#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;36m"
#define WHITE "\033[0;37m"
#define MAX 255

char cBuf[MAX], hBuf[MAX], uBuf[MAX], dBuf[MAX];
/*
void* prompt(char cBuf[]) {
	char hBuf[MAX], uBuf[MAX], dBuf[MAX];
	char* now;
	void* ret;

	gethostname(hBuf, MAX);
	getlogin_r(uBuf, MAX);
	getcwd(dBuf, MAX);



	return ret;
}
*/

int main(int argc, char** argv) {

	/* Declare Vars */
	// char cBuf[MAX];
	char *arg;
	void *full_command; 
	pid_t pid;
	int status;
	char path[BUFSIZ];	// Now path
	struct passwd *pwd;	// User info
	
	/* Consider Exceptions of Input Command  */

	/* Define Each Vars as value */
	if((pwd = getpwuid(getuid())) == NULL) {
		if(errno == 0 || errno == ENOENT || errno == ESRCH || errno == EBADF || errno == EPERM) {
			printf("%sUndeclared User%s\n", RED, WHITE);
			return 1;
		}
		else {
			printf("%sError: %s%s\n", RED, strerror(errno), WHITE);
			return 1;
		}
	}

	gethostname(hBuf, MAX);
	getlogin_r(uBuf, MAX);
	getcwd(dBuf, MAX);

	while(1) {
		// 쉘 앞부분 출력
		printf("%s%s@%s%s:%s%s%s$ ", PURPLE, hBuf, uBuf, WHITE, BLUE, dBuf, WHITE);
		// cBuf에 명령어 입력받기
		full_command = fgets(cBuf, MAX, stdin);
		// 명령어의 끝이 엔터라면(명령어 입력이 끝났다면)
		if(cBuf[strlen(cBuf) - 1] == '\n') cBuf[strlen(cBuf) - 1] = '\0';
		printf("cBuf: %s.end.\n", cBuf);
		if(strcmp(cBuf, "switch") == 0) {
			printf("cBuf is switch.\n");
			execl("/bin/bash", "bash", (char*) NULL);
			perror("Exec Failed");
			exit(EXIT_FAILURE);
			printf("This line should not be reached.\n");
		}
		// else if(strcmp(cBuf, "exit") == 0) break;
		else {
			pid = fork();
			if(pid < 0) { perror("Fork Failed"); exit(EXIT_FAILURE); }
			// 명령어 실행
			else if(pid == 0) { 
				execlp(cBuf, cBuf, (char*) NULL);
			 // 	if(strcmp(
				perror("Exec Failed"); 
				exit(EXIT_FAILURE); 
			}
			else waitpid(pid, NULL, 0);
		}
	}
	printf("Out of while\n");
	return 0;
}
	
	/* Put Command and Execute */
	/*while(prompt(cBuf)) {
		// getcwd(path, BUFSIZ);
		if((pid = fork()) < 0) perror("Fork Error\n");

		if(strcmp(cBuf, "exit") == 0) exit(0);
		else if(pid == 0) {
			strtok(cBuf, " ");
			arg = strtok(NULL, " ");

			if(arg == NULL) execlp(cBuf, cBuf, (char*) 0);
			else {
				if(strcmp(cBuf, "cd") == 0) {
					_cd("/env/");
					chdir(arg);
					_exit(0);
				}
				else execlp(cBuf, cBuf, arg, (char*) 0);
			}
			perror("Couldn't execute\n");
		}
		waitpid(pid, &status, 0);
	}
	exit(0);
}*/
