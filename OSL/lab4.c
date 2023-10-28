// 1. Write a program to find the inode number of an existing file in a directory. Take the 
// input as a filename and print the inode number of the file.
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

void main() {
    char fileName[100];
    printf("Enter filename ");
    scanf("%s", fileName);
    struct stat fileStat;
    stat(fileName, &fileStat);
    printf("Inode: %ld\n", fileStat.st_ino);
}

// 2. Write a program to print out the complete stat structure of a file.
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>

void main() {
    char fileName[100], timeStr[32], fileMode[11];
    printf("Enter filename ");
    scanf("%s", fileName);
    struct stat fileStat;
    stat(fileName, &fileStat);
    time_t t = fileStat.st_atime;
    struct tm * timeStamp = localtime(&t);
    strftime(timeStr, sizeof(timeStr), "%a %Y-%m-%d %H:%M:%S", timeStamp);
    fileMode[0] = (S_ISDIR(fileStat.st_mode)) ? 'd' : '-';
    fileMode[1] = (fileStat.st_mode & S_IRUSR) ? 'r' : '-';
    fileMode[2] = (fileStat.st_mode & S_IWUSR) ? 'w' : '-';
    fileMode[3] = (fileStat.st_mode & S_IXUSR) ? 'x' : '-';
    fileMode[4] = (fileStat.st_mode & S_IRGRP) ? 'r' : '-';
    fileMode[5] = (fileStat.st_mode & S_IWGRP) ? 'w' : '-';
    fileMode[6] = (fileStat.st_mode & S_IXGRP) ? 'x' : '-';
    fileMode[7] = (fileStat.st_mode & S_IROTH) ? 'r' : '-';
    fileMode[8] = (fileStat.st_mode & S_IWOTH) ? 'w' : '-';
    fileMode[9] = (fileStat.st_mode & S_IXOTH) ? 'x' : '-';
    fileMode[10] = '\0';
    printf("Device ID: %ld\nFile Serial No: %ld\nMode of file: %s\nNo. of hard links: %ld\nTime of last access: %s\n", fileStat.st_dev, fileStat.st_ino, fileMode, fileStat.st_nlink, timeStr);
}

//-->
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

void main(int argc,char* argv[100])
{
    if(argc!=2)
    {
        printf("ERROR Insufficient Arguments\n");
        return;
    }
    struct stat sbuf;
    int ret=stat(argv[1],&sbuf);
    if(ret==-1)
    {
        perror("ERROR !!!\n");
        return;
    }
    printf("Device ID containing the file : %ld\t\n",sbuf.st_dev);
    printf("Inode Number : %ld\t\n",sbuf.st_ino);
    printf("Permissions : %d\t\n",sbuf.st_mode);
    printf("No.of Hard links : %ld\t\n",sbuf.st_nlink);
    printf("Owner User ID : %d\t\n",sbuf.st_uid);
    printf("Group User ID : %d\t\n",sbuf.st_gid);
    printf("Device ID : %ld\t\n",sbuf.st_rdev);
    printf("Total Size in bytes : %ld\t\n",sbuf.st_size);
    printf("Block Size : %ld\t\n",sbuf.st_blksize);
    printf("No. of Blocks allocated : %ld\t\n",sbuf.st_blocks);
    printf("Last Access Time : %ld\t\n",sbuf.st_atime);
    printf("Last Modification Time : %ld\t\n",sbuf.st_mtime);
    printf("Last Status Change Time : %ld\t\n",sbuf.st_ctime);
}

// 3. Write a program to create a new hard link to an existing file and unlink the same. 
// Accept the old path as input and print the newpath.
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


// 4. Write a program to create a new soft link to an existing file and unlink the same. 
// Accept the old path as input and print the newpath.
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
