#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PURPLE "\033[0;35m"
#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;36m"
#define WHITE "\033[0;37m"

#define MAX_LENGTH 128

void _ls(char* path);
void _cd(char* path_to);
void _pwd(char* path);
void _cp(FILE* fp);
void _mv(FILE* org, char* name_to);
void _rm(FILE* fp);
void _mkdir(char* name);
void _rmdir(char* path);
void _touch(char* name);
void _cat(FILE* fp);
void _grep(FILE* fp, char* text);
void _echo(char* text);
void _ps(void);
void _kill(void);
void _chmod(FILE* fp, char* auth);
void _chown(FILE* fp, char* user_name);
void _history(void);
void _man(char* command);
void _df(void);
void _du(FILE* fp);
void _find(char* name);
void _diff(FILE* fp1, FILE* fp2);
