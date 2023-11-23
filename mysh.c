#include "mysh.h"

char type(mode_t mode) {
	if(S_ISREG(mode)) return('-');
	if(S_ISDIR(mode)) return('d');
	if(S_ISCHR(mode)) return('c');
	if(S_ISBLK(mode)) return('b');
	if(S_ISLNK(mode)) return('l');
	if(S_ISFIFO(mode)) return('p');
	if(S_ISSOCK(mode)) return('s');
}	// Return type of file

char* perm(mode_t mode) {
	static char perms[10];
	strcpy(perms, "----------");
	for(int i = 0; i < 3; i++) {
		if(mode & (S_IRUSR >> i * 3)) perms[i * 3] = 'r';
		if(mode & (S_IWUSR >> i * 3)) perms[i * 3 + 1] = 'w';
		if(mode & (S_IXUSR >> i * 3)) perms[i * 3 + 2] = 'x';
	}
	return(perms);
}	// Return permission of file

void printStat(char *path, char* file, struct stat *st) {
	printf("%5d ", st->st_blocks);
	printf("%c%s ", type(st->st_mode), perm(st->st_mode));
	printf("%3d ", st->st_nlink);
	printf("%s %s ", getpwuid(st->st_uid)->pw_name, getgrgid(st->st_gid)->gr_name);
	printf("%9d ", st->st_size);
	printf("%.12s ", ctime(&st->st_mtime) + 4);
	printf("%s\n", file);
}	// Print stat info of file

/* $ls: Print directory list */
void _ls(char* path, char* opt) {
	if(path[strlen(path) - 1] != '/') strcat(path, "/");
	DIR *target = opendir(path);
	struct stat st;
	struct dirent *entry;
	char each_path[BUFSIZ + 1];

	// Directory not found exception
	if(target == NULL) perror(path);

	// Print information of each files in directory
	while((entry = readdir(target)) != NULL) {
		sprintf(each_path, "%s/%s", path, entry->d_name);
		if(lstat(each_path, &st) < 0) perror(each_path);
		else printStat(each_path, entry->d_name, &st);
	}
	closedir(target);
}

/* $cd: Move focus to another directory */
void _cd(char* path_to) {
}

/* $pwd: Print path of working directory */
void _pwd(char* path) {
}

/* $cp: Copy file or directory */
void _cp(char* path_from, char* path_to, char* opt) {
}

/* $mv: Move(rename) file or directory */
void _mv(char* path_from, char* path_to, char* opt) {
}

/* $rm: Remove file or directory */
void _rm(char* path, char* opt) {
}

/* $mkdir: Make directory */
void _mkdir(char* path, char* name, char* opt) {
}

/* $rmdir: Remove directory */
void _rmdir(char* path, char* opt) {
}

/* $touch: Make or update (empty) file */
void _touch(char* path, char* name, char* opt) {
}

/* $cat: Print texts of file */
void _cat(FILE* fp, char* opt) {
}

/* $grep: Search words in file and print it */
void _grep(FILE* fp, char* word, char* opt) {
}

/* $echo: Print texts (of file) or value of variable */
void _echo(char* text, char* opt) {
}

/* $ps: Print list of working processes */
void _ps(char* opt) {
}

/* $kill: Kill process */
void _kill(int pid, char* opt) {
}

/* $chmod: Change authority of file or directory */
void _chmod(char* path, char* perm, char* opt) {
}

/* $chown: Change owner of file or directory */
void _chown(char* path, char* user_name, char* opt) {
}

/* $history: Print list of used commands */
void _history(void) {
}

/* $man: Show manual page of command */
void _man(char* command, char* opt) {
}

/* $df: Print state of disk */
void _df(char* opt) {
}

/* $du: Print the disk amount of file or directory */
void _du(char* path, char* opt) {
}

/* $find: Find file or directory */
void _find(char* path, char* name, char* opt) {
}

/* $diff: Compare contents of files and print difference */
void _diff(FILE* fp1, FILE* fp2) {
}
