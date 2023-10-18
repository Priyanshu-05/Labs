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
    printf("Enter new path "); //    /home/student/210905100/Lab4/temp2/temp.txt
    scanf("%s", newPath);
    int res = link(oldPath, newPath);
    if (res == 0) {
        res = unlink(oldPath);
        if (res == 0)
            printf("New path to the file: %s\n", newPath);
        else
            printf("Error unlinking\n");
    }
    else
        printf("Error linking\n");
}

/*Output: ./q3
Enter old path /home/student/210905100/Lab4/temp1/temp.txt
Enter new path /home/student/210905100/Lab4/temp2/temp.txt
New path to the file: /home/student/210905100/Lab4/temp2/temp.txt
*/
