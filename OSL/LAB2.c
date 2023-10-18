/* 1. Write a C program to emulate the ls -l UNIX command that prints all files in a 
 current directory and lists access privileges, etc. DO NOT simply exec ls -l from the 
 program. */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <locale.h>
#include <langinfo.h>
#include <stdint.h>

char const *perms(__mode_t mode){
	static char local_buff[16] = {0};
	int i = 0;
	//user permissions
	local_buff[i++] = ((mode & S_IRUSR) ? 'r' : '-');
	local_buff[i++] = ((mode & S_IWUSR) ? 'w' : '-');
	local_buff[i++] = ((mode & S_IXUSR) ? 'x' : '-');
	//group permissions
	local_buff[i++] = ((mode & S_IRGRP) ? 'r' : '-');
	local_buff[i++] = ((mode & S_IWGRP) ? 'w' : '-');
	local_buff[i++] = ((mode & S_IXGRP) ? 'x' : '-');
	//other permissions
	local_buff[i++] = ((mode & S_IROTH) ? 'r' : '-');
	local_buff[i++] = ((mode & S_IWOTH) ? 'w' : '-');
	local_buff[i++] = ((mode & S_IXOTH) ? 'x' : '-');

	return local_buff;
}

int main(int argc, char *argv[]){
	DIR *mydir;
	struct dirent *myfile;
	struct stat mystat;
	if(argc == 1)
		mydir = opendir(".");
	else
		mydir = opendir(argv[1]);
	
	while((myfile = readdir(mydir)) != NULL){
		bzero(&mystat, sizeof(mystat));
		stat(myfile->d_name, &mystat);
		printf("%10.10s", perms(mystat.st_mode));
		printf("\t%d", mystat.st_uid);
		printf("\t%ld\t",mystat.st_size);
		printf("%s\t", ctime(&mystat.st_mtime));
		printf("%s\n", myfile->d_name);
	}
	closedir(mydir);
}

// 2. Write a program that will list all files in a current directory and all files in 
// subsequent subdirectories.
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>

void executeFunc(char* dir, int depth){
	struct dirent *myfile;
	struct stat mystat;
	DIR *mydir = opendir(dir);
	chdir(dir);
	while((myfile = readdir(mydir)) != NULL){
		bzero(&mystat, sizeof(mystat));
		stat(myfile->d_name, &mystat);
		for(int i=0;i<depth;i++)
			printf(" ");
		printf("%s", myfile->d_name);
		if(S_ISDIR(mystat.st_mode))
			printf("/");
		printf("\n");
		if(S_ISDIR(mystat.st_mode) && strcmp(myfile->d_name, ".") != 0 && strcmp(myfile->d_name, "..") != 0){
			executeFunc(myfile->d_name, depth+1);
		}
	}
	chdir("..");
	closedir(mydir);
}

int main(){
	executeFunc(".", 0);
	return 0;
}

// 1. Write a program that will only list subdirectories in alphabetical order.
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>

int is_directory(const char *path) {
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISDIR(path_stat.st_mode);
}

int compare_strings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory_path>\n", argv[0]);
        return 1;
    }
    
    DIR *dir_ptr = opendir(argv[1]);
    if (dir_ptr == NULL) {
        fprintf(stderr, "Cannot open directory: %s\n", argv[1]);
        return 1;
    }
    
    struct dirent *entry;
    char *subdirs[100]; // Adjust the size as needed
    
    int subdir_count = 0;
    
    while ((entry = readdir(dir_ptr)) != NULL) {
        if (is_directory(entry->d_name) && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            subdirs[subdir_count] = strdup(entry->d_name);
            subdir_count++;
        }
    }
    
    qsort(subdirs, subdir_count, sizeof(char *), compare_strings);
    
    for (int i = 0; i < subdir_count; i++) {
        printf("%s\n", subdirs[i]);
        free(subdirs[i]);
    }
    
    closedir(dir_ptr);
    
    return 0;
}

// 2. Write a program that allows the user to remove any or all of the files in a current 
// working directory. The name of the file should appear followed by a prompt as to 
// whether it should be removed.
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

void printFiles(char* dir)
{
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    dp=opendir(dir);
    if(!dp)
    {
        printf("Cannot open directory : %s\n",dir);
        exit(0);
    }
    chdir(dir);
    char c;
    while(entry=readdir(dp))
    {
        lstat(entry->d_name,&statbuf);
        if(!S_ISDIR(statbuf.st_mode))
        {
            printf("Do you want to remove the file (Y|N) : %s\n",entry->d_name);
            scanf(" %c",&c);
            if(c=='Y'||c=='y')
            {
                remove(entry->d_name);
            }
        }
    }
    chdir("..");
}

void main()
{
    char dir[256];
    printf("Enter Directory Name : \t");
    scanf("%s",dir);
    printFiles(dir);
}

