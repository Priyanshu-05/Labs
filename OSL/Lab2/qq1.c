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

char const *getPermissionsString(__mode_t mode){
    static char permissionsStr[16] = {0};
    int i = 0;
    //user permissions
    permissionsStr[i++] = ((mode & S_IRUSR) ? 'r' : '-');
    permissionsStr[i++] = ((mode & S_IWUSR) ? 'w' : '-');
    permissionsStr[i++] = ((mode & S_IXUSR) ? 'x' : '-');
    //group permissions
    permissionsStr[i++] = ((mode & S_IRGRP) ? 'r' : '-');
    permissionsStr[i++] = ((mode & S_IWGRP) ? 'w' : '-');
    permissionsStr[i++] = ((mode & S_IXGRP) ? 'x' : '-');
    //other permissions
    permissionsStr[i++] = ((mode & S_IROTH) ? 'r' : '-');
    permissionsStr[i++] = ((mode & S_IWOTH) ? 'w' : '-');
    permissionsStr[i++] = ((mode & S_IXOTH) ? 'x' : '-');

    return permissionsStr;
}

int main(int argc, char *argv[]){
    DIR *dirPtr;
    struct dirent *fileEntry;
    struct stat fileStat;
    if(argc == 1)
        dirPtr = opendir(".");
    else
        dirPtr = opendir(argv[1]);
    
    while((fileEntry = readdir(dirPtr)) != NULL){
        bzero(&fileStat, sizeof(fileStat));
        stat(fileEntry->d_name, &fileStat);
        printf("%10.10s", getPermissionsString(fileStat.st_mode));
        printf("\t%d", fileStat.st_uid);
        printf("\t%ld\t", fileStat.st_size);
        printf("%s\t", ctime(&fileStat.st_mtime));
        printf("%s\n", fileEntry->d_name);
    }
    closedir(dirPtr);
}
