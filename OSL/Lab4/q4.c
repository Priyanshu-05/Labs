#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

void main() {

   
    char oldPath[100], newPath[100];
    printf("Enter old path ");
    scanf("%s", oldPath); //    /home/student/210905100/Lab4/temp1/temp.txt
    printf("Enter new path "); //   /home/student/210905100/Lab4/temp2/temp.txt
    scanf("%s", newPath);
    int res = symlink(oldPath, newPath);
    if (res == 0) {
        printf("Symbolic link created\n");

        // res = unlink(oldPath);
        // if (res != 0)
        //     printf("Error unlinking\n");
    }
    else
        printf("Error linking\n");
}