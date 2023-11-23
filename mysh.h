#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <time.h>
#include <dirent.h>
#include <grp.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define PURPLE "\033[0;35m"
#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;36m"
#define WHITE "\033[0;37m"

#define MAX_LENGTH 128

char type(mode_t mode);
char* perm(mode_t mode);
void printStat(char* path, char* file, struct stat* st);

void _ls(char* path, char* opt);
void _cd(char* path_to);
void _pwd(char* path);
void _cp(char* path_from, char* path_to, char* opt);
void _mv(char* path_from, char* path_to, char* opt);
void _rm(char* path, char* opt);
void _mkdir(char* path, char* name, char* opt);
void _rmdir(char* path, char* opt);
void _touch(char* path, char* name, char* opt);
void _cat(FILE* fp, char* opt);
void _grep(FILE* fp, char* word, char* opt);
void _echo(char* text, char* opt);
void _ps(char* opt);
void _kill(int pid, char* opt);;
void _chmod(char* path, char* perm, char* opt);
void _chown(char* path, char* user_name, char* opt);
void _history(void);
void _man(char* command, char* opt);
void _df(char* opt);
void _du(char* path, char* opt);
void _find(char* path, char* name, char* opt);
void _diff(FILE* fp1, FILE* fp2);
